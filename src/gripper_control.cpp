#include <ros/ros.h> 
#include <std_msgs/Float64.h> 
#include <geometry_msgs/PoseArray.h>

#include "baxter_core_msgs/EndEffectorCommand.h"
#include "baxter_core_msgs/EndEffectorState.h"

//https://groups.google.com/a/rethinkrobotics.com/forum/#!topic/brr-users/ZlfK-fqRfuw


ros::Publisher gripper_publisher;


void polarisCB(const geometry_msgs::PoseArray& targets) 
{ 
	//TODO
	baxter_core_msgs::EndEffectorCommand> controlled_grip;
	double distance;

	distance=sqrt(pow(targets.pose[0].position.x-targets.pose[1].position.x)+pow(targets.pose[0].position.y-targets.pose[1].position.y)+pow(targets.pose[0].position.z-targets.pose[1].position.z));


	controlled_grip.command= controlled_grip.CMD_GO
	controlled_grip.id= 65538; //65664  echo the topic 'robot/end_effector/' + name + '/state'
	controlled_grip.args.position=distance;
	controlled_grip.sequence = 3;//1
	controlled_grip.sender = "/grasp_node";


	gripper_publisher.publish(controlled_grip);

}
int main(int argc, char **argv){
	ros::init(argc,argv,"polaris_transformation");
	ros::NodeHandle n; 

	ros::Subscriber polaris_subscriber= n.subscribe("targets",1,polarisCB); 
	ros::Publisher gripper_pub = nh.advertise<baxter_core_msgs/EndEffectorCommand>("/robot/end_effector/left_gripper/command", 1);
	gripper_publisher=gripper_pub;
	
	ros::Rate naptime(1);


	naptime.sleep();


	ros::spin(); 
	return 0;
}
	 
	