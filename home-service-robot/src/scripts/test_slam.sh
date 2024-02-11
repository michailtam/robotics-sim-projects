#!/bin/sh
xterm  -e  " source devel/setup.bash " &
sleep 5
xterm  -e  " roslaunch my_robot world.launch" &
sleep 5
xterm  -e  " rosrun rviz rviz -d $(pwd)/src/rvizConfig/robot_model.rviz" &
sleep 5
xterm  -e  " roslaunch my_robot mapping.launch" &
sleep 5
xterm  -e  " rosrun teleop_twist_keyboard teleop_twist_keyboard.py"