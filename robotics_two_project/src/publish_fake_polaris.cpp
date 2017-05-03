// Zeta coordinator
// December, 2016

#include<ros/ros.h>
#include <baxter_fk_ik/baxter_kinematics.h>
#include <cartesian_planner/baxter_cartesian_planner.h>
#include <baxter_trajectory_streamer/baxter_trajectory_streamer.h>

#include<baxter_trajectory_streamer/trajAction.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <coordinator/ManipTaskAction.h>
#include <object_manipulation_properties/object_ID_codes.h>
#include <object_finder/objectFinderAction.h>
#include <object_grabber/object_grabberAction.h>
#include <geometry_msgs/PoseArray.h>
#include <std_msgs/Int32.h>


geometry_msgs::PoseArray g_des_flange_pose_stamped_wrt_torso;


using namespace std;



int main(int argc, char** argv) {
    ros::init(argc, argv, "publish_fake_data"); // name this node 
    ros::NodeHandle nh; //standard ros node handle

    ros::Publisher fake_data = nh.advertise<geometry_msgs::PoseArray>("index_finger_pose_wrt_polaris", 100);
    geometry_msgs::PoseStamped temp_pose;
    geometry_msgs::Quaternion temp_msg;

    geometry_msgs::PoseArray temp_array;
    temp_array.header.frame_id = "base";
    temp_pose.pose.position.x = 0.65;
    temp_pose.pose.position.y = -0.25;
    temp_pose.pose.position.z = 0.01;

    double x_min = 0.25;
    double x_max = 0.7;
    double y_min = -0.5;
    double y_max = 0.1;
    double z_min = 0.0;
    double z_max = 0.3;
    
    temp_array.poses.push_back(temp_pose.pose);
    //g_des_flange_pose_stamped_wrt_torso.poses[0].position.y = -0.25;
    //g_des_flange_pose_stamped_wrt_torso.poses[0].position.z = 0.01; //-0.125; //pose w/rt world frame
    //g_des_flange_pose_stamped_wrt_torso.poses[0].orientation.x = 0.0;
    //g_des_flange_pose_stamped_wrt_torso.poses[0].orientation.y = 0.0;
    //g_des_flange_pose_stamped_wrt_torso.poses[0].orientation.z = 0.0;
    //g_des_flange_pose_stamped_wrt_torso.poses[0].orientation.w = 0.0;
    //g_des_flange_pose_stamped_wrt_torso.header.stamp = ros::Time::now();
    fake_data.publish(temp_array);

    while (ros::ok()){
	fake_data.publish(temp_array);

        temp_pose.pose.position.y = temp_pose.pose.position.y - (rand()%3 - 1)*0.03;
	temp_pose.pose.position.x = temp_pose.pose.position.x - (rand()%3 - 1)*0.02;
	temp_pose.pose.position.z = temp_pose.pose.position.z - (rand()%3 - 1)*0.02;
	temp_array.poses.clear();
	temp_array.poses.push_back(temp_pose.pose);
	ros::Duration(1.0).sleep();
	ros::spinOnce();
	}

    //

    //ros::spinOnce();
    return 0;


}

