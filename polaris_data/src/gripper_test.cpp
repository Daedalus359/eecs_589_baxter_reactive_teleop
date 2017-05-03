#include <ros/ros.h> 
#include <std_msgs/Float64.h> 
#include <geometry_msgs/PoseArray.h>

#include "baxter_core_msgs/EndEffectorCommand.h"
#include "baxter_core_msgs/EndEffectorState.h"

ros::Publisher gripper_publisher;

void polarisCB(const geometry_msgs::PoseArray& targets) 
{ 
	//TODO
	baxter_core_msgs::EndEffectorCommand controlled_grip;
	double distance;
	double map_dist; //variable for mapping the distance to the position of the gripper

	distance=sqrt(pow(targets.poses[0].position.x-targets.poses[1].position.x,2)+pow(targets.poses[0].position.y-targets.poses[1].position.y,2)+pow(targets.poses[0].position.z-targets.poses[1].position.z,2));

	map_dist=(distance-0.03) *909;

	ROS_INFO("mapped_dist= %f",map_dist);


	controlled_grip.command= controlled_grip.CMD_GO;
	controlled_grip.id= 65538; //65664  echo the topic 'robot/end_effector/' + name + '/state'
	controlled_grip.command=map_dist;
	controlled_grip.sequence = 3;//1
	controlled_grip.sender = "/grasp_node";

	ros::Time start =  ros::Time::now();   
	while((ros::Time::now() - start) < ros::Duration(1)) {
	gripper_publisher.publish(controlled_grip);
	//ros::Duration(0.05);
	}

}

int main(int argc, char **argv){
	ros::init(argc,argv,"polaris_transformation");
	ros::NodeHandle n; 

	ros::Subscriber polaris_subscriber= n.subscribe("/polaris_sensor/targets",1,polarisCB); 
	ros::Publisher gripper_pub = n.advertise<baxter_core_msgs::EndEffectorCommand>("/robot/end_effector/left_gripper/command", 1);
	gripper_publisher=gripper_pub;
	
	//ros::Rate naptime(1);


	//naptime.sleep();


	ros::spin(); 

	//return 0;
}
	 

