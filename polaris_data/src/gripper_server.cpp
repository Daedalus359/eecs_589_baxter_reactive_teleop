//created by Ammar Nahari

#include <ros/ros.h>
#include <std_msgs/Float64.h> 

#include "baxter_core_msgs/EndEffectorCommand.h"
#include <sstream>

#include <polaris_data/GripperSrvMsg.h>
#include <iostream>
using namespace std;

ros::Publisher gripper_publisher;
double map_dist;


bool callback(polaris_data::GripperSrvMsgRequest& request, polaris_data::GripperSrvMsgResponse& response){

	ROS_INFO("received position : %f",request.grip_pos);
	response.grip_done=false;
 

	baxter_core_msgs::EndEffectorCommand controlled_grip;
	std::ostringstream args;


	args << "{\"position\":" << request.grip_pos << ", \"dead zone\": 5.0, \"force\": 40.0, \"holding force\": 30.0, \"velocity\": 50.0}";
	
	
	//controlled_grip.command= baxter_core_msgs::EndEffectorCommand::CMD_RESET;
	//naptime.sleep();
	//controlled_grip.command= baxter_core_msgs::EndEffectorCommand::CMD_CALIBRATE;
	//naptime.sleep();
	controlled_grip.command= baxter_core_msgs::EndEffectorCommand::CMD_GO;	
	controlled_grip.id= 65538; //65664  echo the topic 'robot/end_effector/' + name + '/state'
	controlled_grip.command= args.str();//{"position":map_dist};
	controlled_grip.sequence = 1;//3
	controlled_grip.sender = "/grip_node";


	ros::Time start =  ros::Time::now();  
	while((ros::Time::now() - start) < ros::Duration(3)) {
		gripper_publisher.publish(controlled_grip);
		ros::Duration(0.05);
	}

	response.grip_done= true;

	return true;
}


int main(int argc, char **argv){

  ros::init(argc, argv, "gripper_service");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("gripper_position", callback);
  ros::Publisher gripper_pub = n.advertise<baxter_core_msgs::EndEffectorCommand>("/robot/end_effector/right_gripper/command", 1);

  gripper_publisher=gripper_pub;

  ROS_INFO("Ready to accept gripper position.");


  ros::spin();

  return 0;
}
