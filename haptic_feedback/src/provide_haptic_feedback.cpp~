#include <sound_play/sound_play.h>
#include <unistd.h>
#include <baxter_core_msgs/EndEffectorState.h>

double g_latest_gripper_force;

void sleepok(int t, ros::NodeHandle &nh){
	if(nh.ok()){
		sleep(t);
	}
}

//TODO: I may need an include statement to support the message type below

void gripperStateCallback(const baxter_core_msgs::EndEffectorState& new_state){
	g_latest_gripper_force = new_state.force;
}

int main(int argc, char** argv){
	ros::init(argc, argv, "sound_play_test");
	ros::NodeHandle nh;

	ros::Subscriber gripper_state_subscriber = nh.subscribe("/robot/end_effector/right_gripper/state",1,gripperStateCallback);

	sound_play::SoundClient sc;
	
	sleepok(1,nh);//I think I can remove this one
	
	while(nh.ok()){
	
		if(g_latest_gripper_force == 0.0)
		{
			ROS_INFO("Playing no sound");
		}
		else if(g_latest_gripper_force < 2.0)
		{
			ROS_INFO("Playing volume for force %f", g_latest_gripper_force);
			sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol20.wav");
		}
		else if(g_latest_gripper_force < 4.0)
		{
			ROS_INFO("Playing volume for force %f", g_latest_gripper_force);
			sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol19.wav");
		}
		else if(g_latest_gripper_force < 6.0)
		{
			ROS_INFO("Playing volume for force %f", g_latest_gripper_force);
			sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol18.wav");
		}
		else if(g_latest_gripper_force < 8.0)
		{
			ROS_INFO("Playing volume for force %f", g_latest_gripper_force);
			sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol17.wav");
		}
		else if(g_latest_gripper_force < 10.0)
		{
			ROS_INFO("Playing volume for force %f", g_latest_gripper_force);
			sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol16.wav");
		}
		else if(g_latest_gripper_force < 12.0)
		{
			ROS_INFO("Playing volume for force %f", g_latest_gripper_force);
			sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol15.wav");
		}
		else if(g_latest_gripper_force < 14.0)
		{
			ROS_INFO("Playing volume for force %f", g_latest_gripper_force);
			sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol14.wav");
		}
		else if(g_latest_gripper_force < 16.0)
		{
			ROS_INFO("Playing volume for force %f", g_latest_gripper_force);
			sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol13.wav");
		}
		else if(g_latest_gripper_force < 18.0)
		{
				ROS_INFO("Playing volume for force %f", g_latest_gripper_force);
			sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol12.wav");
		}
		else if(g_latest_gripper_force < 20.0)
		{
			ROS_INFO("Playing volume for force %f", g_latest_gripper_force);
			sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol11.wav");
		}
		else if(g_latest_gripper_force < 22.0)
		{
			ROS_INFO("Playing volume for force %f", g_latest_gripper_force);
			sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol10.wav");
		}
		else if(g_latest_gripper_force < 24.0)
		{
			ROS_INFO("Playing volume for force %f", g_latest_gripper_force);
			sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol9.wav");
		}
		else if(g_latest_gripper_force < 26.0)
		{
			ROS_INFO("Playing volume for force %f", g_latest_gripper_force);
			sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol8.wav");
		}
		else if(g_latest_gripper_force < 28.0)
		{
			ROS_INFO("Playing volume for force %f", g_latest_gripper_force);
			sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol7.wav");
		}
		else if(g_latest_gripper_force < 30.0)
		{
			ROS_INFO("Playing volume for force %f", g_latest_gripper_force);
			sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol6.wav");
		}
		else if(g_latest_gripper_force < 32.0)
		{
			ROS_INFO("Playing volume for force %f", g_latest_gripper_force);
			sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol5.wav");
		}
		else if(g_latest_gripper_force < 34.0)
		{
			ROS_INFO("Playing volume for force %f", g_latest_gripper_force);
			sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol4.wav");
		}
		else if(g_latest_gripper_force < 36.0)
		{
			ROS_INFO("Playing volume for force %f", g_latest_gripper_force);
			sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol3.wav");
		}
		else if(g_latest_gripper_force < 38.0)
		{
			ROS_INFO("Playing volume for force %f", g_latest_gripper_force);
			sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol2.wav");
		}
		else
		{
			ROS_WARN("Playing loudest sound, unexpected force range");
			sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol1.wav");
		}


		ros::Duration(0.1).sleep();
		ros::spinOnce();
	}
	
	return 0;
}
