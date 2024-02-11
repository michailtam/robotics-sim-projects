//NOTE: Very nice explanation of TF and they can be used: https://articulatedrobotics.xyz/ready-for-ros-6-tf/

#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "obstacle_detector_pkg/obstacle_detector_node.hpp"
#include "obstacle_detector_pkg/obstacle_monitor_node.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto obs_detector_node = std::make_shared<tf2::ObstacleDetector_node>();
    auto obs_monitor_node = std::make_shared<tf2::ObstacleMonitor_node>();

    // To execute both nodes in parallel you have to use an executor and add each node to it.
    // After that you are able to spin both in parallel.
    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(obs_detector_node->get_node_base_interface());
    executor.add_node(obs_monitor_node->get_node_base_interface());
    executor.spin();

    rclcpp::shutdown();

    return 0;
}