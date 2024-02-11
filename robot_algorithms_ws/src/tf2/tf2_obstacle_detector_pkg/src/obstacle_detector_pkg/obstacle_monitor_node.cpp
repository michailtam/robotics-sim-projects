#include "obstacle_detector_pkg/obstacle_monitor_node.hpp"


namespace tf2
{
    ObstacleMonitor_node::ObstacleMonitor_node() : Node("obstacle_monitor_node"), 
        tf_buffer(), tf_listener_(tf_buffer)
    {   
        // Creates the publisher to publish a marker (e.g. for RViz) and a timer to call the control loop
        // that runs in 2Hz, which retrieves the latest TF frame (i.e. obstacle position)
        marker_pub_ = this->create_publisher<visualization_msgs::msg::Marker>("obstacle_marker", 1);
        timer_ = this->create_wall_timer(500ms, std::bind(&ObstacleMonitor_node::control_cycle, this));
    }

    void ObstacleMonitor_node::control_cycle()
    {
        geometry_msgs::msg::TransformStamped robot2obstacle; // Defines the message to publish.

        // Tries to calculate the geometric transformation from one frame to another 
        // (even if there is no direct relationship) and gets the last available one.
        try {
            robot2obstacle = tf_buffer.lookupTransform("base_footprint", "detected_obstacle", tf2::TimePointZero);
        } catch (tf2::TransformException& e) {
            RCLCPP_WARN(this->get_logger(), "Latest obstacle transform not found: %s", e.what());
            return;
        }

        // Fills the message with the coordinates retrieved from the /obstacle_marker topic.
        double x = robot2obstacle.transform.translation.x;
        double y = robot2obstacle.transform.translation.y;
        double z = robot2obstacle.transform.translation.z;
        double theta = atan2(y, x);

        // Publishes the coordinates via the /ros_out topic and stdout
        RCLCPP_INFO(this->get_logger(), "Obstacle detected at (%lf m, %lf m, %lf m) = %lf rads", x, y, z, theta);

        // Sends the visual marker
        this->send_marker(x, y, z);
    }

    void ObstacleMonitor_node::send_marker(double x, double y, double z)
    {
        visualization_msgs::msg::Marker obstacle_arrow;
        obstacle_arrow.header.frame_id = "base_footprint";
        obstacle_arrow.header.stamp = now();
        obstacle_arrow.type = visualization_msgs::msg::Marker::ARROW; // Creates an arrow marker
        obstacle_arrow.action = visualization_msgs::msg::Marker::ADD;
        obstacle_arrow.lifetime = rclcpp::Duration(1s); // Sets the duration for the marker to 1 sec.

        // Defines the start position of the marker.
        geometry_msgs::msg::Point start;
        start.x = 0.0;
        start.y = 0.0;
        start.z = 0.0;
        // Defines the end position of the marker.
        geometry_msgs::msg::Point end;
        end.x = x;
        end.y = y;
        end.z = z;
        obstacle_arrow.points = {start, end};

        // Defines the color of the marker and scales it appropriately (here red).
        obstacle_arrow.color.r = 1.0;
        obstacle_arrow.color.g = 0.0;
        obstacle_arrow.color.b = 0.0;
        obstacle_arrow.color.a = 1.0;
        obstacle_arrow.scale.x = 0.02;
        obstacle_arrow.scale.y = 0.1;
        obstacle_arrow.scale.z = 0.1;

        marker_pub_->publish(obstacle_arrow); // Publishes the marker which can be retrieved by RViz.
    }
}
