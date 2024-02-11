#include "obstacle_detector_pkg/obstacle_detector_node.hpp"


namespace tf2
{
    ObstacleDetector_node::ObstacleDetector_node() : Node("obstacle_detector_node"), 
            tf_buffer_(), tf_listener_(tf_buffer_)
    {   
        scan_sub_ = this->create_subscription<sensor_msgs::msg::LaserScan>("/input_scan",
            rclcpp::SensorDataQoS(), std::bind(&tf2::ObstacleDetector_node::scan_callback, this, _1));
        
        tf_broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(*this);
    }

    void ObstacleDetector_node::scan_callback(const sensor_msgs::msg::LaserScan::UniquePtr msg)
    {
        double distance = msg->ranges[msg->ranges.size() / 2]; // Reads the center laser scan position

        if(!std::isinf(distance)) 
        {
            tf2::Transform laser2object;
            laser2object.setOrigin(tf2::Vector3(distance, 0.0, 0.0));
            laser2object.setRotation(tf2::Quaternion(0.0, 0.0, 0.0, 1.0));

            geometry_msgs::msg::TransformStamped odom2laser_msg;
            tf2::Stamped<tf2::Transform> odom2laser;

            try {
                odom2laser_msg = tf_buffer_.lookupTransform(
                    "odom", "base_laser_link",
                    tf2::timeFromSec(rclcpp::Time(msg->header.stamp).seconds() - 0.3));
                tf2::fromMsg(odom2laser_msg, odom2laser);
            } catch (tf2::TransformException & ex) {
              RCLCPP_WARN(get_logger(), "Obstacle transform not found: %s", ex.what());
              return;
            }

            tf2::Transform odom2object = odom2laser * laser2object;

            geometry_msgs::msg::TransformStamped odom2object_msg;
            odom2object_msg.transform = tf2::toMsg(odom2object);

            odom2object_msg.header.stamp = msg->header.stamp;
            odom2object_msg.header.frame_id = "odom";
            odom2object_msg.child_frame_id = "detected_obstacle";

            tf_broadcaster_->sendTransform(odom2object_msg); // Sends the transform to the TF subsystem.
        }
    }
} // namespace tf2
