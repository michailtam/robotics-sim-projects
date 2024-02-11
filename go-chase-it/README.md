# Robotics Simulation - Go Chase It
In this robotics simulation a custom *mobile robot* chases a white ball in an office building, which gets moved by the user in the envoronment to different places. The simulation gets performed in [gazebo](http://gazebosim.org/). The camera attached to the robot reads visual data to determine if there is a white ball or not. The ([Lidar](https://en.wikipedia.org/wiki/Lidar)) laser scanner gets used to map the environment. The interactions of the robot are implemented using [ROS-Kinetic](https://www.ros.org/) and C++. To track what the robot is sensing the 3D visualization tool [Rviz tool for ROS](http://wiki.ros.org/rviz) is used. 

### Features
- Only white balls are getting chased (e.g. if the robot sees red ball it stops)
- The robot changes its move direction based on odometry measurements
- When there is no ball in its view range, the robot stops immediately
- To get the image from the camera the robot subscribes to the **/camera/rgb/image_raw topic**
- To get the data from the laser scanner the robot subsrcibes to the **/scan topic**
- The supported laser scanners in ROS can be found [here](http://wiki.ros.org/Sensors#A2D_range_finders)

### White ball determination algorithm
To determine the orientation the robot has to move after it has seen a white ball, each image captured by the camera gets divided into a left, front and right part. This operation gets executed by the functions ```process_image_callback(const sensor_msgs::Image img)``` and ```determine_ball_position(int pos, int width) ```. The first one takes as parameter the current image and checks if the image contains a white ball. If this is the case, the function processes the index number of the column and the width of the image. This is necessary, because the robot has to calculate the linear x and angular z velocities to strafe the robot towards the ball. After the function has returned these values, the ```drive_bot(vel.linear_x, vel.angular_z)``` function calls the service ```command_robot``` which executes the movement of the robot.

### Prerequisites
This project assumes that you are using Ubuntu (tested on Ubuntu 20.4 LST) and that ROS, gazebo and all required packages
are installed. The installation instructions can be found [here](http://wiki.ros.org/kinetic/Installation/Ubuntu) and [here](http://gazebosim.org/tutorials?tut=install_ubuntu).

### Installation
To install the repository and packages, please follow the bellow steps. If you encounter any problems please refer to the [disussion forum of ROS](https://discourse.ros.org/) to get further help.

1. Clone the repository ```$ git clone https://github.com/michailtam/go-chase-it.git```
2. Change into the **src** folder ```$ cd src``` and initialize the workspace ```$ catkin_init_workspace```
3. Return to the toplevel catkin folder and build the packages```$ catkin_make```

### Running the simulation:
To run the simulation follow the following steps:

Open a terminal, change into the toplevel of the catkin_workspace and issue: 
```./test_ball_chase.sh```

Alternatively you can execute each script seperately with the following steps:
1. Open a terminal change into the toplevel of the catkin workspace and issue
```
$ source devel/setup.bash
$ roslaunch my_robot world.launch
```
2. Open a second terminal (also change to toplevel) and issue
```
$ source devel/setup.bash
$ roslaunch ball_chaser ball_chaser.launch
```

### Rviz
Rviz is pre-configured with default parameters to perform the chase. Feel free to adjust these parameters to your needs.

The overall process to run the simulation and to see how the robot chases white balls is shown in the video below.

#### Video
<a href="https://www.youtube.com/embed/0WqCSpGcEX0" target="_blank">
<img src="https://github.com/michailtam/robotics-go-chase-it/blob/master/images/video_preview.png" alt="Go Chase It (ROS) Video" width="760" height="400" border="0" />
