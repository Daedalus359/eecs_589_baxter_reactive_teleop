#include <sound_play/sound_play.h>
#include <unistd.h>

double g_latest_gripper_force = 0.0;

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

	ros::Subscriber gripper_state_subscriber = nh.subscribe("/robot/end_effector/left_gripper_state",1,gripperStateCallback);

	sound_play::SoundClient sc;
	
	sleepok(1,nh);//I think I can remove this one
	
	while(nh.ok()){
			
		ROS_INFO("Playing sound");

		sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol1.wav");
		sleepok(2, nh);

		ros::spinOnce();
	}
	
	return 0;
}
