import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch.conditions import (IfCondition, UnlessCondition)


def generate_launch_description():
    # Get the launch directory
    pkg_bringup_share = get_package_share_directory('mobile_base_bringup')
    conf_file = os.path.join(pkg_bringup_share, 'rviz', 'rviz_conf.rviz')
    
    # Launch configuration variables specific to simulation
    use_config_file = LaunchConfiguration('use_config_file', default='False')
    
    declare_rviz_config_file_cmd = DeclareLaunchArgument(
        name='use_config_file',
        default_value=use_config_file,
        description='Full path to the RVIZ config file to use.')
    
    rviz_cmd_yes = Node(
        condition=IfCondition(use_config_file),
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        parameters=[{'use_sim_time': True}],
        arguments=['-d', conf_file],
        output='screen')
    
    rviz_cmd_no = Node(
        condition=UnlessCondition(use_config_file),
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        parameters=[{'use_sim_time': True}],
        output='screen')
        
  
    # Create the launch description and populate
    ld = LaunchDescription()

    # Declares the launch options
    ld.add_action(declare_rviz_config_file_cmd)
    
    # Adds any conditioned actions
    ld.add_action(rviz_cmd_yes)
    ld.add_action(rviz_cmd_no)

    return ld   
    