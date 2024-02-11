#!/bin/sh
xterm  -e  " source devel/setup.bash " &
sleep 5
xterm  -e  " roslaunch my_robot world.launch" &
sleep 5
xterm  -e  " roslaunch ball_chaser ball_chaser.launch"