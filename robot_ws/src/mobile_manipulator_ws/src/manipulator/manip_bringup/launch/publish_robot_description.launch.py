#!/usr/bin/python3
# -*- coding: utf-8 -*-

'''
Launch script to start Gazebo (and optional Rviz) and publish a robot description topic (i.e. a robot)
Example: $ ros2 launch <package_name> spawn_robot_in_gazebo_launch.py world:=warehouse
NOTE: Check all available launch arguments by executing the above and appending -s.
You can specify more than one argument while executing e.g. .... world:=warehouse- use_sim_time:=True ...
'''

import os
from launch import LaunchDescription
from launch.substitutions import (Command, LaunchConfiguration)
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.conditions import (IfCondition, UnlessCondition)
from launch.actions import DeclareLaunchArgument
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    # Sets the path to required packages.
    pkg_share = FindPackageShare(package='manip_description').find('manip_description')

    # Sepcifies launch arguments received from the command line.
    use_sim_time = LaunchConfiguration('use_sim_time', default='true')
    use_joint_state_pub_ui = LaunchConfiguration('use_joint_state_pub_ui', default='False')
    
    # Process the URDF file
    urdf_path = os.path.join(pkg_share,'urdf', 'manip_robot.urdf.xacro') 
    robot_description = ParameterValue(Command(['xacro ', urdf_path]), value_type=str)

    declare_urdf_model = DeclareLaunchArgument(
        name='xacro_file', 
        default_value=urdf_path, 
        description='Absolute path to the robot urdf file')
    
    # Subscribes to the joint states of the robot, and publishes the 3D pose of each link.
    start_robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[{
            'use_sim_time': use_sim_time, 
            'robot_description': robot_description}],
        )

    # NOTE: Only one of the following two joint publishers can be executed at the same time. Otherwise, the
    # the /joint_state topic will receive multiple joint states, which cases issues.

    # Publishes the joint state values for the non-fixed joints in the URDF file.
    start_joint_state_publisher_node = Node(
        condition=UnlessCondition(use_joint_state_pub_ui),
        package='joint_state_publisher',
        executable='joint_state_publisher',
        # parameters=[{'robot_description': robot_description}],
        name='joint_state_publisher',
    )

    # Publishes the joint state values and shows the UI to set the joints.
    start_joint_state_publisher_ui_cmd = Node(
        condition=IfCondition(use_joint_state_pub_ui),
        package='joint_state_publisher_gui',
        executable='joint_state_publisher_gui',
        name='joint_state_publisher_gui',
        # parameters=[{'robot_description': robot_description}],
        output='screen')

    # Creates the launch description and populate.
    ld = LaunchDescription()
    
    # Adds the actions.
    ld.add_action(declare_urdf_model)
    ld.add_action(start_robot_state_publisher_node)
    ld.add_action(start_joint_state_publisher_node)
    ld.add_action(start_joint_state_publisher_ui_cmd)
    
    return ld



