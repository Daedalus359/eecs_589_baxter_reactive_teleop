# eecs_589_baxter_reactive_teleop
Your description goes here

## Example usage

## Running tests/demos

rosrun polaris_sensor polaris_sensor_node _roms:="$(rospack find polaris_sensor)/rom/Right_Finger.rom,$(rospack find polaris_sensor)/rom/Left_Finger.rom" _port:=/dev/ttyUSB0

rostopic echo /polaris_sensor/targets


rosrun eecs_589_baxter_reactive_teleop polaris_transformation
rosrun eecs_589_baxter_reactive_teleop gripper_control