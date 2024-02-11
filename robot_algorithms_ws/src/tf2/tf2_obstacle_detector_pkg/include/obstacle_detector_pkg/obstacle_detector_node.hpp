#ifndef TF2_DETECTOR_NODE_CPP__
#define TF2_DETECTOR_NODE_CPP__

#include "rclcpp/rclcpp.hpp"

// TF2 libraries
#include "tf2_ros/static_transform_broadcaster.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include <tf2/transform_datatypes.h>
#include <tf2/LinearMath/Quaternion.h>
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

#include "sensor_msgs/msg/laser_scan.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

/*
This class implements a TF2 Detector, which is able to receive tf2 frames and publish
transforms to the TF subsystem via the /tf_static topic.
NOTE: If you want to publish non-static transforms you need to publish a TransformBroadcaster message
via the /tf topic.
*/

namespace tf2
{   
    class ObstacleDetector_node : public rclcpp::Node
    {
        public:
            ObstacleDetector_node();

        private:
            void scan_callback(const sensor_msgs::msg::LaserScan::UniquePtr msg);

            rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr scan_sub_;
            std::shared_ptr<tf2_ros::StaticTransformBroadcaster> tf_broadcaster_;
            tf2::BufferCore tf_buffer_;
            tf2_ros::TransformListener tf_listener_;
    };
}

#endif // TF2_DETECTOR_NODE_CPP__