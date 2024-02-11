#ifndef TF2_MONITOR_NODE_CPP__
#define TF2_MONITOR_NODE_CPP__

#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_listener.h"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "visualization_msgs/msg/marker.hpp"
#include <memory>

using namespace std::chrono_literals;
using std::placeholders::_1;

/*
This class implements a TF2 Monitor, which is able to receive tf2 frames and publish
visualmarkers...
*/

namespace tf2
{   
    class ObstacleMonitor_node : public rclcpp::Node
    {
        public:
            ObstacleMonitor_node();

        private:
            void control_cycle();
            void send_marker(double x, double y, double z);
            rclcpp::TimerBase::SharedPtr timer_;
            
            tf2::BufferCore tf_buffer;
            tf2_ros::TransformListener tf_listener_;

            rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_pub_;
    };
}

#endif // TF2_MONITOR_NODE_CPP__