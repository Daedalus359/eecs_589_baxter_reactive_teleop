//created by Ammar Nahari

#include <ros/ros.h>
#include <std_msgs/Float64.h> 
#include <geometry_msgs/PoseArray.h>


#include <polaris_data/GripperSrvMsg.h>
#include <iostream>
using namespace std;

double map_dist=100;

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
int main(int argc, char **argv) {
    ros::init(argc, argv, "gripper_client");
    ros::NodeHandle n;

   	ros::Subscriber polaris_subscriber= n.subscribe("/polaris_sensor/targets",1,polarisCB); 
    ros::ServiceClient client = n.serviceClient<polaris_data::GripperSrvMsg>("gripper_position");
    polaris_data::GripperSrvMsg srv;


    while (ros::ok()) {
    	srv.request.grip_pos= map_dist;
    	if (client.call(srv)){
    		while(!srv.response.grip_done){
    			ROS_INFO("sent position %f, waiting for excecution", map_dist);
    		}
    	}
    	else{
    		ROS_ERROR("Failed to call service gripper_position");
    		return 1;
    	}

    	ros::spinOnce();

    }

    //ros_spinOnce();
    return 0;
}
