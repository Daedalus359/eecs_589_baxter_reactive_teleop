#include <sound_play/sound_play.h>
#include <unistd.h>

void sleepok(int t, ros::NodeHandle &nh){
	if(nh.ok()){
		sleep(t);
	}
}

int main(int argc, char** argv){
	ros::init(argc, argv, "sound_play_test");
	ros::NodeHandle nh;
	sound_play::SoundClient sc;
	
	sleepok(1,nh);//I think I can remove this one
	
	while(nh.ok()){
			
		ROS_INFO("Playing sound");

		sc.playWave("/home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/haptic_feedback/wav_files/250hz_tenth_vol1.wav");
		sleepok(2, nh);
	}
	
	return 0;
}
