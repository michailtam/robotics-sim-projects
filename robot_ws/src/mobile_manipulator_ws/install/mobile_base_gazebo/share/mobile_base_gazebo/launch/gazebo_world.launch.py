#!/usr/bin/python3
# -*- coding: utf-8 -*-

'''
NOTE: You have to change the paths, depended to your system and ROS distribution.
'''
import os
from launch import LaunchDescription
from launch.actions import (DeclareLaunchArgument, IncludeLaunchDescription, ExecuteProcess)
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import (LaunchConfiguration, PythonExpression, PathJoinSubstitution)
from launch_ros.substitutions import (FindPackageShare, FindPackagePrefix)


def generate_launch_description():
    # Sets the paths to the Gazebo packages.
    pkg_gazebo_ros = FindPackageShare(package='gazebo_ros').find('gazebo_ros')
    pkg_robot_gazebo = FindPackageShare(package='mobile_base_gazebo').find('mobile_base_gazebo')

    # Set the path to the world and model files.
    world_path = os.path.join(pkg_robot_gazebo, 'worlds')
    gazebo_models_path = os.path.join(pkg_robot_gazebo, 'models')

    # Sets the Gazebo model path.
    if 'GAZEBO_MODEL_PATH' in os.environ:
        # Checks if there is an additional custom model folder and if it is not empty to append it.
        if os.path.exists(gazebo_models_path) and os.listdir(gazebo_models_path) != 0:
            os.environ['GAZEBO_MODEL_PATH'] = os.environ['GAZEBO_MODEL_PATH'] + ':' + gazebo_models_path
        else:
            os.environ['GAZEBO_MODEL_PATH'] = '/usr/share/gazebo-11/models'
    else:
        os.environ['GAZEBO_MODEL_PATH'] = '/usr/share/gazebo-11/models'

    # Sets the Gazebo plugin path.
    if 'GAZEBO_PLUGIN_PATH' in os.environ:
        # Checks if there is an additional custom plugins folder and appends it.
        if os.path.exists(os.path.join(pkg_robot_gazebo, 'lib')) and os.listdir(os.path.join(pkg_robot_gazebo, 'lib')) != 0:
            os.environ['GAZEBO_PLUGIN_PATH'] = os.environ['GAZEBO_PLUGIN_PATH'] + ':' + os.path.join(pkg_robot_gazebo, 'lib')
        else:
            os.environ['GAZEBO_PLUGIN_PATH'] = '/opt/ros/humble/lib'
    else:
        os.environ['GAZEBO_PLUGIN_PATH'] = '/opt/ros/humble/lib'

    # Displays the paths
    print('GAZEBO_MODEL_PATH: ', str(os.environ['GAZEBO_MODEL_PATH']))
    print('GAZEBO_PLUGIN_PATH: ', str(os.environ['GAZEBO_PLUGIN_PATH']))

    # Launch configuration variables specific to simulation
    headless = LaunchConfiguration('headless')
    use_sim_time = LaunchConfiguration('use_sim_time')
    use_simulator = LaunchConfiguration('use_simulator')
    world = LaunchConfiguration('world')

    declare_simulator = DeclareLaunchArgument(
        name='headless',
        default_value='False',
        description='Whether to execute gzclient')
    
    declare_use_sim_time = DeclareLaunchArgument(
        name='use_sim_time',
        default_value='true',
        description='Use simulation (Gazebo) clock if true')

    declare_use_simulator = DeclareLaunchArgument(
        name='use_simulator',
        default_value='True',
        description='Whether to start the simulator')

    declare_world = DeclareLaunchArgument(
        name='world',
        default_value='empty',
        description='SDF world file')
    
    # Starts the Gazebo server.
    start_gazebo_server = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(pkg_gazebo_ros, 'launch', 'gzserver.launch.py')),
        condition=IfCondition(use_simulator),
        launch_arguments={'world': [PathJoinSubstitution([world_path, world]), '.world']}.items())

    # Starts the Gazebo client.    
    start_gazebo_client = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(pkg_gazebo_ros, 'launch', 'gzclient.launch.py')),
        condition=IfCondition(PythonExpression([use_simulator, ' and not ', headless])))
    
    # start_gazebo_cmd =  ExecuteProcess(
    #     cmd=['gazebo', '--verbose','-s', 'libgazebo_ros_init.so', '-s', 'libgazebo_ros_factory.so'],
    #     output='screen')

    # Creates the launch description and populate.
    ld = LaunchDescription()
    
    # Declares the launch options.
    ld.add_action(declare_simulator)
    ld.add_action(declare_use_sim_time)
    ld.add_action(declare_use_simulator)
    ld.add_action(declare_world)

    # Adds the actions.
    # ld.add_action(start_gazebo_cmd)
    ld.add_action(start_gazebo_server)
    ld.add_action(start_gazebo_client)

    return ld

