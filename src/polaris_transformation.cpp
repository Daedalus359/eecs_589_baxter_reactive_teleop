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

	right_pose.poses.position.x=targets.pose[0].point.x;
	right_pose.poses.position.y=targets.pose[0].point.y;
	right_pose.poses.position.z=-targets.pose[0].point.z;

	right_pose.poses.orientation.x=targets.pose[0].quaternion.x;
	right_pose.poses.orientation.y=-targets.pose[0].quaternion.y;
	right_pose.poses.orientation.z=-targets.pose[0].quaternion.z;
	right_pose.poses.orientation.w=-targets.pose[0].quaternion.w;



	left_pose.header.stamp = targets.header.stamp;
	left_pose.header.frame_id = "/base";

	left_pose.poses.position.x=targets.pose[1].point.x;
	left_pose.poses.position.y=targets.pose[1].point.y;
	left_pose.poses.position.z=-targets.pose[1].point.z;

	left_pose.poses.orientation.x=targets.pose[1].quaternion.x;
	left_pose.poses.orientation.y=-targets.pose[1].quaternion.y;
	left_pose.poses.orientation.z=-targets.pose[1].quaternion.z;
	left_pose.poses.orientation.w=-targets.pose[1].quaternion.w;


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
	 
	