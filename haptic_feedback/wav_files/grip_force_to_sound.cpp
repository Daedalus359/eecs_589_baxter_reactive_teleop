#include <sound_play/sound_play.h>
#include <unistd.h>

int main(int argc, char **argv){
	ros::init(argc, argv, "sound_play_test");
	ros::NodeHandle nh;
	sound_play::SoundClient sc;
	sound_play::SoundClient quiet_sc;

	while(nh.ok()){
		sc.playWave("/usr/share/xemacs21/xemacs-packages/etc/sounds/boing.wav");
		//TODO: get one wav file per 10 volume and then make this play the right one based on a value maintained by the
		sleepok(0.1, nh);
	}
}
