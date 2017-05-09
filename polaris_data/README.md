# eecs_589_baxter_reactive_teleop
Your description goes here

## Polaris tracking 

Clone the folloing two repositories and follow te instructions for installing polaris_sensor and serial:
- https://github.com/axn337/serial
- https://github.com/axn337/polaris_sensor

from eecs_589_baxter_reactive_teleop/polaris_data/rom/:
copy Left_Finger.rom and Right_Finger.rom and past them in:polaris_sensor/rom/

Run the following command to start traking right and left finger: 
rosrun polaris_sensor polaris_sensor_node _roms:="$(rospack find polaris_sensor)/rom/Right_Finger.rom,$(rospack find polaris_sensor)/rom/Left_Finger.rom" _port:=/dev/ttyUSB0

To echo polaris sensor data:
rostopic echo /polaris_sensor/targets

Run this code to fix polaris transformation and publish /right_finger_wrt_polaris and /left_finger_wrt_polaris:
rosrun eecs_589_baxter_reactive_teleop polaris_transformation

## Gripper code running and testing

enable baxter before running gripper code using:
rosrun baxter_tools enable_robot.py -e

Run positional gripper control:
rosrun eecs_589_baxter_reactive_teleop gripper_control

Run binary gripper control:
rosrun eecs_589_baxter_reactive_teleop gripper_test

manual positional gripper control:
rostopic pub -1 /robot/end_effector/right_gripper/command baxter_core_msgs/EndEffectorCommand '{ id :  65538,  command : go, args : "{ \"position\": 50.0, \"dead zone\": 5.0, \"force\": 40.0, \"holding force\": 30.0, \"velocity\": 50.0}", sender : "foo", "sequence" : 1 }'

Echoing /right_gripper/state topic:
rostopic echo /robot/end_effector/right_gripper/state


## baxter simulator
roslaunch baxter_gazebo baxter_world.launch
rosrun baxter_tools enable_robot.py -e
rosrun baxter_examples joint_position_keyboard.py
