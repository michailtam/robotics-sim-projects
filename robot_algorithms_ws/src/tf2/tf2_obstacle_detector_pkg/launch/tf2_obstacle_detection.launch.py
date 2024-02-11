from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    object_detector = Node(
            package='obstacle_detector_pkg',
            executable='obstacle_detector_main',
            output='screen',
            parameters=[{
                'use_sim_time': True,
            }],
            remappings=[
                ('input_scan', '/scan_raw')]
    )

    ld = LaunchDescription()
    ld.add_action(object_detector)
    return ld
