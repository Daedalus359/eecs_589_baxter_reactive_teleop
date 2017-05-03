## Using the haptic feedback:
it appears that sound will play from the computer running the soundplay node, even when on baxter_master. Therefore, the audio cable for the haptic feedback earbuds should be plugged into this same computer.

With a roscore running, start up the soundplay node, which acts as a server for playing sounds:
	rosrun sound_play soundplay_node.py

To test this, you may wish to use an ordinary set of earbuds or speakers, and run the following command in another terminal:

	rosrun sound_play say.py "hello world"

If everything is working, you should hear "hello world" said through the speakers.
Please note that some TCP/IP error occasionally causes soundplay_node to require a restart.

Next, you can execute the following command:

	rosrun haptic_feedback play_sounds

This node will verify whether all sound files are in the right place for use in the actual haptic feedback. Listening during execution of this node, you should hear a brief pulse of sound once every second.

If this did not work, please make sure that you have the provided wav files in the right location. By default, the program looks for them in:

 /home/kevinbradner/ros_ws/src/eecs_589_baxter_reactive_teleop/wav_files/250hz_tenth_vol1.wav

If you wish to change this, simply write the correct path to the sound files for your machine and recompile.
