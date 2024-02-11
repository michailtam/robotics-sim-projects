# Launch file to handle an EKF (Extended Kalman Filter) in ROS using Turtlebot Gazebo and Rviz - ROBOTICS
The repsitory contains a launch file which comprises the necessary nodes (i.e. ROS packages) to start the turtlebot in the gazebo world, use a fake lazer, execute a pose ekf, plot using the ekf plotter, handles the odometry trajectory, handles the turtlebot teleop keyboard and starts Rviz containing all the necessary settings to track the path the robot is traversing. The red and green paths denote the filtered and unfiltered trajectories as the robot moves and collects sensor data. In this context Rviz gets used to show that the EKF (Extended Kalman Filter) filters out uncertainties and estimates the robot pose while it is moving in space.

## Prerequisites
Using this launch file presupposes that all the following packages are installed (cloned):
- turtlebot_simulator
- turtlebot
- robot_pose_efk
- odom_to_trajectory

The packages can be installed cloning the following repos in the src folder of your catkin workspace (e.g. catkin_ws/src)
```
git clone https://github.com/turtlebot/turtlebot_simulator
git clone https://github.com/udacity/robot_pose_ekf 
git clone https://github.com/udacity/odom_to_trajectory
git clone https://github.com/turtlebot/turtlebot
```
Another place to search for ROS packages is [here](https://www.ros.org/browse/list.php?package_type=package&distro=kinetic).

## Important
Don't forget to source your catkin workspace and install the dependencies (if needed). For example to install dependencies for the turtlebot_teleop package issue the following in the terminal.
```
source devel/setup.bash
rosdep -i install turtlebot_teleop
```
