#!/usr/bin/python3
# -*- coding: utf-8 -*-
import os
from launch import LaunchDescription
from launch.actions import (IncludeLaunchDescription, RegisterEventHandler, LogInfo)
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.substitutions import FindPackageShare
from launch.event_handlers import OnExecutionComplete, OnProcessExit
from launch_ros.actions import Node


def generate_launch_description():

    # Defines the packages to use.
    pkg_robot_bringup_pkg = FindPackageShare(package='mobile_base_bringup').find('mobile_base_bringup')
    pkg_robot_gazebo_pkg = FindPackageShare(package='mobile_base_gazebo').find('mobile_base_gazebo')

    # Starts the robot publisher node.
    start_robot_publisher_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_robot_bringup_pkg, 'launch', 'publish_robot_description.launch.py')))

    # Starts Gazebo
    start_gazebo_world_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_robot_gazebo_pkg, 'launch', 'gazebo_world.launch.py')))
    
    # Spawns the robot in Gazebo
    start_robot_spawn_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_robot_gazebo_pkg, 'launch', 'spawn_robot.launch.py')))
    
    # ROS2 control
    # NOTE: To spawn the robot in ROS2 Humble change any reference of spawner.py to just spawner. 
    start_diff_drive_spawner = Node(
        package="controller_manager",
        executable="spawner",
        output='screen',
        arguments=['mobile_base_velocity_controller', '-c', '/controller_manager'],
    )

    start_joint_broad_spawner = Node(
        package="controller_manager",
        executable="spawner",
        output='screen',
        arguments=['joint_state_broadcaster', '-c', '/controller_manager'],
    )

    # Make sure start_diff_drive_spawner starts after start_joint_broad_spawner
    diffdrive_controller_spawn_callback = RegisterEventHandler(
        event_handler=OnProcessExit(
            target_action=start_joint_broad_spawner,
            on_exit=[start_diff_drive_spawner],
        )
    )

    ld = LaunchDescription()

    # Adds the actions.
    ld.add_action(start_gazebo_world_cmd)
    ld.add_action(start_robot_publisher_cmd)
    # ld.add_action(start_diff_drive_spawner)
    # ld.add_action(start_joint_broad_spawner)
    ld.add_action(diffdrive_controller_spawn_callback)
    ld.add_action(start_robot_spawn_cmd)
    
    return ld



