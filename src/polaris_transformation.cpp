#include <ros/ros.h> 
#include <std_msgs/Float64.h> 
#include <geometry_msgs/PoseArray.h>
#include <cmath>



ros::Publisher right_finger_publisher;
ros::Publisher left_finger_publisher;


void polarisCB(const geometry_msgs::PoseArray& targets) 
{ 
	//TODO
	geometry_msgs::PoseArray right_pose;
	geometry_msgs::PoseArray left_pose;

	right_pose.header.stamp = targets.header.stamp;
	right_pose.header.frame_id = "/base";

	right_pose.pose.position.x=targets.pose[0].position.x;
	right_pose.pose.position.y=targets.pose[0].position.y;
	right_pose.pose.position.z=-targets.pose[0].position.z;

	right_pose.pose.orientation.x=targets.pose[0].orientation.x;
	right_pose.pose.orientation.y=-targets.pose[0].orientation.y;
	right_pose.pose.orientation.z=-targets.pose[0].orientation.z;
	right_pose.pose.orientation.w=-targets.pose[0].orientation.w;



	left_pose.header.stamp = targets.header.stamp;
	left_pose.header.frame_id = "/base";

	left_pose.pose.position.x=targets.pose[1].position.x;
	left_pose.pose.position.y=targets.pose[1].position.y;
	left_pose.pose.position.z=-targets.pose[1].position.z;

	left_pose.pose.orientation.x=targets.pose[1].orientation.x;
	left_pose.pose.orientation.y=-targets.pose[1].orientation.y;
	left_pose.pose.orientation.z=-targets.pose[1].orientation.z;
	left_pose.pose.orientation.w=-targets.pose[1].orientation.w;


	right_finger_publisher.publish(right_pose);
	left_finger_publisher.publish(left_pose);

}
int main(int argc, char **argv){
	ros::init(argc,argv,"polaris_transformation");
	ros::NodeHandle n; 

	ros::Subscriber polaris_subscriber= n.subscribe("targets",1,polarisCB); 
	ros::Publisher right_finger_pub = nh.advertise<geometry_msgs::PoseArray>("right_finger_wrt_polaris", 1);
	right_finger_publisher= right_finger_pub;
	ros::Publisher left_finger_pub = nh.advertise<geometry_msgs::PoseArray>("left_finger_wrt_polaris", 1);
	left_finger_publisher= left_finger_pub;
	
	ros::Rate naptime(1);


	naptime.sleep();


	ros::spin(); 
	return 0;
}
	 
	