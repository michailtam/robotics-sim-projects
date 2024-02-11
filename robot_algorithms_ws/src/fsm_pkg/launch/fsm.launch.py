from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='fsm_pkg',
            executable='fsm_node_cpp',
            output='screen',
            parameters=[{
                'use_sim_time': True,
            }],
            remappings=[
                ('input_scan', '/scan_raw'),
                ('output_vel', '/nav_vel')
            ]
        )
    ])
