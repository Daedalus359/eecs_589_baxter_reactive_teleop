

#include<ros/ros.h>
#include <baxter_fk_ik/baxter_kinematics.h>
#include <cartesian_planner/baxter_cartesian_planner.h>
#include <baxter_trajectory_streamer/baxter_trajectory_streamer.h>
#include <math.h>

#include<baxter_trajectory_streamer/trajAction.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <coordinator/ManipTaskAction.h>
#include <object_manipulation_properties/object_ID_codes.h>
#include <object_finder/objectFinderAction.h>
#include <object_grabber/object_grabberAction.h>
#include <geometry_msgs/PoseArray.h>
#include <std_msgs/Int32.h>
bool g_goal_done = true;
int g_callback_status = coordinator::ManipTaskResult::PENDING;
int g_object_grabber_return_code = 0;
int g_object_finder_return_code = 0;
int g_fdbk_count = 0;
int g_objectid;
bool get_polaris = false;
bool is_nan = false;

geometry_msgs::PoseArray g_des_flange_pose_stamped_wrt_torso;
geometry_msgs::PoseStamped temp_pose;
coordinator::ManipTaskResult g_result;


using namespace std;

int g_done_count=0;
void rightArmDoneCb(const actionlib::SimpleClientGoalState& state, const baxter_trajectory_streamer::trajResultConstPtr& result) {
    ROS_INFO(" rtArmDoneCb: server responded with state [%s]", state.toString().c_str());
    ROS_INFO("got return val = %d", result->return_val);
    g_done_count++;
}



// Called once when the goal becomes active; not necessary, but possibly useful for diagnostics

void activeCb() {
    ROS_INFO("Goal just went active");
}




void get_polaris_frame_callBack(const geometry_msgs::PoseArray &polaris_pose) {
    //hard code an object pose; later, this will come from perception
    //specify reference frame in which this pose is expressed:
    //will require that "system_ref_frame" is known to tf
    //g_des_flange_pose_stamped_wrt_torso.header.frame_id = arm_pose.header.frame_id; //set object pose; ref frame must be connected via tf



    if (isnan(polaris_pose.poses[0].position.x) == 0){

        g_des_flange_pose_stamped_wrt_torso.poses.clear();

        //Ammar added offsets in the pos x and neg y directions

        temp_pose.pose.position.x = 0.2 + polaris_pose.poses[0].position.x;
        temp_pose.pose.position.y = polaris_pose.poses[0].position.y-0.1;
        temp_pose.pose.position.z = polaris_pose.poses[0].position.z;
        
        g_des_flange_pose_stamped_wrt_torso.poses.push_back(temp_pose.pose);
        
        //g_des_flange_pose_stamped_wrt_torso.poses[0].position.x = polaris_pose.poses[0].position.x;
        //g_des_flange_pose_stamped_wrt_torso.poses[0].position.y = polaris_pose.poses[0].position.y;
        //g_des_flange_pose_stamped_wrt_torso.poses[0].position.z = polaris_pose.poses[0].position.z; //-0.125; //pose w/rt world frame
        //g_des_flange_pose_stamped_wrt_torso.poses[0].orientation.x = polaris_pose.poses[0].orientation.x;
        //g_des_flange_pose_stamped_wrt_torso.poses[0].orientation.y = polaris_pose.poses[0].orientation.y;
        //g_des_flange_pose_stamped_wrt_torso.poses[0].orientation.z = polaris_pose.poses[0].orientation.z;
        //g_des_flange_pose_stamped_wrt_torso.poses[0].orientation.w = polaris_pose.poses[0].orientation.w;
        //g_des_flange_pose_stamped_wrt_torso.header.stamp = ros::Time::now();

        // adjust the polaris frame to represent the transformation between the two
        get_polaris = true;
    }

}

geometry_msgs::PoseArray get_polaris_arm_pose() {
    return g_des_flange_pose_stamped_wrt_torso;
}


int main(int argc, char** argv) {
    ros::init(argc, argv, "robotics_two_coordinator"); // name this node 
    ros::NodeHandle nh; //standard ros node handle

    // Subscribe to the polaris node to get new values for the position of the arm
    ros::Subscriber sub = nh.subscribe("left_finger_wrt_polaris", 1, get_polaris_frame_callBack);

    // Tool flange positions
    Eigen::Affine3d a_toolflange_start, a_toolflange_end;
    std::vector<Eigen::VectorXd> optimal_path;
    trajectory_msgs::JointTrajectory des_trajectory_right;

    // Get the geometry message of the pose from polaris
    geometry_msgs::PoseArray polaris_pose;

    // more

    Eigen::VectorXd q_vec_right_arm;
    //some handy constants...
    Eigen::Matrix3d R_flange_horiz;
    Eigen::Vector3d flange_n_des, flange_t_des, flange_b_des;
    Eigen::Vector3d flange_origin;
    bool found_path = false;

    std::vector<Eigen::VectorXd> des_path_right;

    // instantiate a baxter forward and inverse kinematics solver

    Baxter_fwd_solver baxter_fwd_solver;
    Baxter_IK_solver baxter_ik_solver;

    // instantiate a baxter cartesian planner
    CartTrajPlanner cartTrajPlanner;

    Baxter_traj_streamer baxter_traj_streamer(&nh); //instantiate a Baxter_traj_streamer object and pass in pointer to nodehandle for constructor to use  
    // warm up the joint-state callbacks; want to make sure the joint states are valid
    cout << "warming up callbacks..." << endl;
    for (int i = 0; i < 100; i++) {
        ros::spinOnce();  //the baxter_traj_streamer needs spins for its updates
        ros::Duration(0.01).sleep();
    }

    // goal objects compatible with the arm servers
    baxter_trajectory_streamer::trajGoal goal_right;
    // Adjust the polaris coordinates to the baxter coordinate system


    //instantiate clients of the two arm servers:
    actionlib::SimpleActionClient<baxter_trajectory_streamer::trajAction> right_arm_action_client("rightArmTrajActionServer", true);

    // attempt to connect to the servers:
    ROS_INFO("waiting for right-arm server: ");
    bool server_exists = right_arm_action_client.waitForServer(ros::Duration(1.0));
    while (!server_exists) {
        ROS_WARN("waiting on right-arm server...");
        ros::spinOnce();
        ros::Duration(1.0).sleep();
        server_exists = right_arm_action_client.waitForServer(ros::Duration(1.0));
    }
    ROS_INFO("connected to right-arm action server"); // if here, then we connected to the server; 


    // Send the coordinates to the trajectory streamer

    // wait to get first message from callback

    while(get_polaris == false){
        ROS_WARN("waiting on polaris callback");
        ros::spinOnce();
        ros::Duration(1.0).sleep();
    }


    Eigen::Affine3d current_location;
    Eigen::Vector3d p;
    Eigen::Vector3d n_des,t_des,b_des;
    Vectorq6x1 q_in;
    q_in<<0,0,0,0,0,0;

    b_des<<0,0,-1; //tool flange pointing down
    n_des<<1,0,0; //x-axis pointing forward...arbitrary
    t_des = b_des.cross(n_des); //consistent right-hand frame
    
    Eigen::Matrix3d R_des;
    R_des.col(0) = n_des;
    R_des.col(1) = t_des;
    R_des.col(2) = b_des;



    Eigen::Affine3d a_tool_des; // expressed in DH frame  
    a_tool_des.linear() = R_des;
    a_toolflange_start.linear() = R_des;
    a_toolflange_end.linear() = R_des;

    Eigen::Vector3d p_des;




   q_vec_right_arm = baxter_traj_streamer.get_q_vec_right_arm_Xd();
   current_location = baxter_fwd_solver.fwd_kin_flange_wrt_torso_solve(q_vec_right_arm);
   std::cout << current_location.translation() << std::endl;

   // Initial arm pose of tool
    des_path_right.push_back(q_vec_right_arm);


    p_des[0] = current_location.translation()[0];
    p_des[1] = current_location.translation()[1];
    p_des[2] = current_location.translation()[2];
    a_toolflange_start.translation() = p_des;

    p_des[0] = 0.5;
    p_des[1] = -0.35;
    p_des[2] = 0.01;
    a_toolflange_end.translation() = p_des;


    found_path = cartTrajPlanner.cartesian_path_planner(q_vec_right_arm, a_toolflange_end, optimal_path);

    if (found_path) {
        ROS_INFO("found patf");
        des_path_right.push_back(optimal_path[0]);
        baxter_traj_streamer.stuff_trajectory_right_arm(optimal_path, des_trajectory_right);
        //  copy traj to goal:
        goal_right.trajectory = des_trajectory_right;

        ROS_INFO("sending goals to left and right arms: ");
        right_arm_action_client.sendGoal(goal_right, &rightArmDoneCb); 


        while (g_done_count<1) {
            ROS_INFO("waiting to finish current move");
            ros::spinOnce();
            ros::Duration(0.01).sleep();
        }

        g_done_count = 0;
    
    }
    else {
        ROS_WARN("no path found");
        ros::Duration(0.01).sleep();
    }


    //ros::spinOnce();
    //cout<<"right arm is at: "<<baxter_traj_streamer.get_q_vec_right_arm_Xd().transpose()<<endl;

    
    // return 0;

    
    while (ros::ok()) {
        // repopulate desired arm position from polaris input
        des_path_right.clear();

        while(true){
            is_nan = false;
            q_vec_right_arm = baxter_traj_streamer.get_q_vec_right_arm_Xd();

            for(int i = 0; i < 7; ++i){
                if (isnan(q_vec_right_arm[i]) == 1){
                    is_nan = true;
                }
            }
            if(!is_nan){
                break;
            }

        }  
        //if (!is_nan){
        current_location = baxter_fwd_solver.fwd_kin_flange_wrt_torso_solve(q_vec_right_arm);
        //}
            
        std::cout << current_location.translation() << std::endl;
        ROS_INFO("Current joint position");
        std::cout << q_vec_right_arm << std::endl;

        des_path_right.push_back(q_vec_right_arm);

        // Initial arm pose of tool

        p_des[0] = current_location.translation()[0];
        p_des[1] = current_location.translation()[1];
        p_des[2] = current_location.translation()[2];
        a_toolflange_start.translation() = p_des;

        // get desired pose from call back of 
        polaris_pose = get_polaris_arm_pose();
        get_polaris == false;

        // change the polaris pose and add constants to fit baxter more appropriately
        p_des[0] = polaris_pose.poses[0].position.x;
        p_des[1] = polaris_pose.poses[0].position.y;
        p_des[2] = polaris_pose.poses[0].position.z;
        a_toolflange_end.translation() = p_des;

        found_path = cartTrajPlanner.cartesian_path_planner(q_vec_right_arm, a_toolflange_end, optimal_path);

        if (found_path) {
            ROS_INFO("found path");
            des_path_right.push_back(optimal_path[0]);
            baxter_traj_streamer.stuff_trajectory_right_arm(optimal_path, des_trajectory_right);
            //  copy traj to goal:
            goal_right.trajectory = des_trajectory_right;

            ROS_INFO("sending goals to left and right arms: ");
            right_arm_action_client.sendGoal(goal_right, &rightArmDoneCb); 


            int counter = 0;
            while (g_done_count<1) {
                ROS_INFO("waiting to finish current move");
                ros::spinOnce();
                ros::Duration(0.01).sleep();

                //if (counter > 10 && get_polaris){
                //g_done_count = 1;
                //}
                counter++;
            }
            g_done_count = 0;
        

        }
        else {
            ROS_WARN("no path found");
            ros::Duration(0.01).sleep();
        }
        ros::Duration(0.01).sleep();
        ros::spinOnce();
        ROS_WARN("at the end");

        // send out new desired arm position of arm
    }

return 0;

}
