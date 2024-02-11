#!/usr/bin/python3
# -*- coding: utf-8 -*-
'''
Launch script to start Gazebo (and optional Rviz) and publish a robot description topic (i.e. a robot)
Example: $ ros2 launch <package_name> spawn_robot_in_gazebo_launch.py world:=warehouse
NOTE: Check all available launch arguments by executing the above and appending -s.
You can specify more than one argument while executing e.g. .... world:=warehouse use_sim_time:=True ...
'''

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import (Command, LaunchConfiguration)
from launch_ros.actions import Node


def generate_launch_description():
    # Sets the robot properties
    robot_model_name = 'mobile_base_robot' #NOTE: The name of the robot defined in the urdf file 
    
    # Sepcifies launch arguments received from the command line
    position_x = LaunchConfiguration('x')
    position_y = LaunchConfiguration('y')
    position_z = LaunchConfiguration('z')
    orientation_R = LaunchConfiguration('R')
    orientation_P = LaunchConfiguration('P')
    orientation_Y = LaunchConfiguration('Y')

    # Declares the launch arguments.
    declare_use_sim_time = DeclareLaunchArgument(
        name='use_sim_time',
        default_value='true',
        description='Use simulation (Gazebo) clock if true')

    # Declares the initial postion and orientation
    declare_posx = DeclareLaunchArgument(name='x', default_value='0.0', description='Initial x position')
    declare_posy = DeclareLaunchArgument(name='y', default_value='0.0', description='Initial y position')
    declare_posz = DeclareLaunchArgument(name='z', default_value='0.0', description='Initial z position')
    declare_roll = DeclareLaunchArgument(name='R', default_value='0.0', description='Initial roll degree')
    declare_pitch = DeclareLaunchArgument(name='P', default_value='0.0', description='Initial pitch degree')
    declare_yaw = DeclareLaunchArgument(name='Y', default_value='-1.57', description='Initial yaw degree')
    
    # Spawnes the robot at a given position and with a specific pose
    spawn_entity = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        output='screen',
        arguments=['-entity', robot_model_name,
                   '-topic', '/robot_description',
                    '-x', position_x, '-y', position_y, '-z', position_z,
                    '-R', orientation_R, '-P', orientation_P, '-Y', orientation_Y])

    # Creates the launch description and populate.
    ld = LaunchDescription()
    
    # Declares the launch options.
    ld.add_action(declare_use_sim_time)
    ld.add_action(declare_posx)
    ld.add_action(declare_posy) 
    ld.add_action(declare_posz)
    ld.add_action(declare_roll)
    ld.add_action(declare_pitch)
    ld.add_action(declare_yaw)

    # Adds the actions.
    ld.add_action(spawn_entity)
    
    return ld



