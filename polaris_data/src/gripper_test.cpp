#include <ros/ros.h> 
#include <geometry_msgs/PoseArray.h>
#include <std_msgs/Bool.h>

 std_msgs::Bool grab;
  
void polarisCB(const geometry_msgs::PoseArray& targets) 
{ 
	//TODO
	double distance;
	double grip_th= 0.08;
	double map_dist; //variable for mapping the distance to the position of the gripper

	distance=sqrt(pow(targets.poses[0].position.x-targets.poses[1].position.x,2)+pow(targets.poses[0].position.y-targets.poses[1].position.y,2)+pow(targets.poses[0].position.z-targets.poses[1].position.z,2));
	
	if(distance < grip_th){
		grab.data= true;
		ROS_INFO("Closing");
	}
	else if(distance >=grip_th){
		grab.data= false;
		ROS_INFO("Opening");
	}
	else{
		ROS_WARN("No Data!");
	} 
}

int main(int argc, char **argv){
	ros::init(argc,argv,"polaris_transformation");
	ros::NodeHandle n; 

	ros::Subscriber polaris_subscriber= n.subscribe("/polaris_sensor/targets",1,polarisCB); 
	ros::Publisher gripper= n.advertise<std_msgs::Bool>("close_gripper", 1);
	
	ros::Rate naptime(1000);

	
	//ros::Time start =  ros::Time::now();   
    
    while(ros::ok()) {
		ros::Time start =  ros::Time::now();   
		while((ros::Time::now() - start) < ros::Duration(3)) {
			gripper.publish(grab);
		}
		ros::spinOnce(); 
		naptime.sleep();

    }


	//return 0;
}
	 

