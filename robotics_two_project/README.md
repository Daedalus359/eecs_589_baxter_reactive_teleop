## robotics_two_project

This package includes two 

## Running baxter controller

rosrun baxter_tools enable_robot.py -e
rosrun baxter_trajectory_streamer rt_arm_as
rosrun baxter_trajectory_streamer left_arm_as
rosrun robotics_two_project robotics_two_coordinator

## baxter simulator
roslaunch baxter_gazebo baxter_world.launch
rosrun baxter_tools enable_robot.py -e
rosrun baxter_examples joint_position_keyboard.py
