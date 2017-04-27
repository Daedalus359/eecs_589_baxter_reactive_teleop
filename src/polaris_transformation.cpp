#include <ros/ros.h> 
//#include <std_msgs/Float64.h> 
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/PoseStamped.h>
#include <cmath>



ros::Publisher right_finger_publisher;
ros::Publisher left_finger_publisher;


void polarisCB(const geometry_msgs::PoseArray& targets) 
{ 
	ROS_INFO("polarisCB activated");
	//TODO
	geometry_msgs::PoseArray right_pose;
	geometry_msgs::PoseArray left_pose;

	geometry_msgs::PoseStamped temp_pose;

	right_pose.header.stamp = targets.header.stamp;
	right_pose.header.frame_id = "/base";

	temp_pose.pose.position.x=targets.poses[0].position.x;
	temp_pose.pose.position.y=targets.poses[0].position.y;
	temp_pose.pose.position.z=-targets.poses[0].position.z;

	temp_pose.pose.orientation.x=targets.poses[0].orientation.x;
	temp_pose.pose.orientation.y=-targets.poses[0].orientation.y;
	temp_pose.pose.orientation.z=-targets.poses[0].orientation.z;
	temp_pose.pose.orientation.w=-targets.poses[0].orientation.w;

	right_pose.poses[0]=temp_pose.pose;


	left_pose.header.stamp = targets.header.stamp;
	left_pose.header.frame_id = "/base";

	temp_pose.pose.position.x=targets.poses[1].position.x;
	temp_pose.pose.position.y=targets.poses[1].position.y;
	temp_pose.pose.position.z=-targets.poses[1].position.z;

	temp_pose.pose.orientation.x=targets.poses[1].orientation.x;
	temp_pose.pose.orientation.y=-targets.poses[1].orientation.y;
	temp_pose.pose.orientation.z=-targets.poses[1].orientation.z;
	temp_pose.pose.orientation.w=-targets.poses[1].orientation.w;


	left_pose.poses[0]=temp_pose.pose;


	//ROS_INFO("left %f right %f",left_pose.poses[0].position.x, right_pose.poses[0].position.x );


	right_finger_publisher.publish(right_pose);
	left_finger_publisher.publish(left_pose);

}
int main(int argc, char **argv){
	
	ROS_INFO("start polaris_transformation ");

	ros::init(argc,argv,"polaris_transformation");
	ros::NodeHandle n; 

	ros::Subscriber polaris_subscriber= n.subscribe("/polaris_sensor/targets",1,polarisCB); 
	ros::Publisher right_finger_pub = n.advertise<geometry_msgs::PoseArray>("right_finger_wrt_polaris", 1);
	right_finger_publisher= right_finger_pub;
	ros::Publisher left_finger_pub = n.advertise<geometry_msgs::PoseArray>("left_finger_wrt_polaris", 1);
	left_finger_publisher= left_finger_pub;
	
	//ros::Rate naptime(1);


	//naptime.sleep();

	ros::spin();
	
	//return 0;
}
	 
	