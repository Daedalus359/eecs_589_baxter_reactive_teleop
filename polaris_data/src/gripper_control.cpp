#include <ros/ros.h> 
#include <std_msgs/Float64.h> 
#include <geometry_msgs/PoseArray.h>

#include "baxter_core_msgs/EndEffectorCommand.h"
#include "baxter_core_msgs/EndEffectorState.h"
#include <sstream>

//https://groups.google.com/a/rethinkrobotics.com/forum/#!topic/brr-users/ZlfK-fqRfuw


//ros::Publisher gripper_publisher;
double map_dist=100;
//variable for mapping the distance to the position of the gripper


void polarisCB(const geometry_msgs::PoseArray& targets) 
{ 
	//TODO
	double distance;
	double conv_dist;

	distance=sqrt(pow(targets.poses[0].position.x-targets.poses[1].position.x,2)+pow(targets.poses[0].position.y-targets.poses[1].position.y,2)+pow(targets.poses[0].position.z-targets.poses[1].position.z,2));
	
	
	conv_dist=((distance-0.03) *909);
	
	if(conv_dist>100){
		map_dist=100;
	}
	else if(conv_dist<0){
		map_dist=0;
	}
	else if(conv_dist>0 && conv_dist<100){
		map_dist=conv_dist;
	}
	ROS_INFO("Right x= %f y= %f z= %f",targets.poses[0].position.x,targets.poses[0].position.y,targets.poses[0].position.z);
	ROS_INFO("Left x= %f y= %f z= %f",targets.poses[1].position.x,targets.poses[1].position.y,targets.poses[1].position.z);
	ROS_INFO("mapped_dist= %f",map_dist);
	


}

int main(int argc, char **argv){
	ros::init(argc,argv,"gripper_control");
	ros::NodeHandle n; 

	ros::Subscriber polaris_subscriber= n.subscribe("/polaris_sensor/targets",1,polarisCB); 
	ros::Publisher gripper_pub = n.advertise<baxter_core_msgs::EndEffectorCommand>("/robot/end_effector/right_gripper/command", 1);
	//gripper_publisher=gripper_pub;
	//map_dist
	baxter_core_msgs::EndEffectorCommand controlled_grip;
	std::ostringstream args;
	
	ros::Rate naptime(100);
	
		


	//naptime.sleep();
	while(ros::ok()) {
		args << "{\"position\":" << map_dist << ", \"dead zone\": 5.0, \"force\": 40.0, \"holding force\": 30.0, \"velocity\": 50.0}";
		
		
		//controlled_grip.command= baxter_core_msgs::EndEffectorCommand::CMD_RESET;
		//naptime.sleep();
		//controlled_grip.command= baxter_core_msgs::EndEffectorCommand::CMD_CALIBRATE;
		//naptime.sleep();
		controlled_grip.command= baxter_core_msgs::EndEffectorCommand::CMD_GO;	
		controlled_grip.id= 65538; //65664  echo the topic 'robot/end_effector/' + name + '/state'
		controlled_grip.command=args.str();//{"position":map_dist};
		controlled_grip.sequence = 1;//3
		controlled_grip.sender = "/grasp_node";
		
		
		ros::Time start =  ros::Time::now();  
		while((ros::Time::now() - start) < ros::Duration(3)) {
			gripper_pub.publish(controlled_grip);
			//ros::Duration(0.05);
		}
		ros::spinOnce(); 
		naptime.sleep();
	}

	//return 0;
}
	 
	
