#ifndef FSM_PKG__
#define FSM_PKG__

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <utility>
#include <valarray>

using namespace std::chrono_literals;
using std::placeholders::_1;

/*
This class implements a Finite State Machine
NOTE: Check if the topics have to be remapped appropriately before using the node
*/

namespace fsm_pkg
{
    enum class State {FORWARD, BACK, TURN, STOP};   // FSM-States
    
    class FSM_node : public rclcpp::Node
    {
        public:
            FSM_node();

        private:
            void laserscan_callback(sensor_msgs::msg::LaserScan::UniquePtr msg);
            void control_cycle();
            void go_state(State new_state);

            // State transitions
            bool check_forward_2_back();
            bool check_forward_2_stop();
            bool check_back_2_turn();
            bool check_turn_2_forward();
            bool check_stop_2_forward();
            
            double rad_2_degree(double radians);
            int check_for_obstacle();

            // Robot movement properties
            const rclcpp::Duration TURNING_TIME {2s};
            const rclcpp::Duration BACKING_TIME {1s};
            const rclcpp::Duration SCAN_TIMEOUT {1s};
            static constexpr float SPEED_LINEAR = 0.3f;
            static constexpr float SPEED_ANGULAR = 0.3f;
            static constexpr float OBSTACLE_DISTANCE = 0.3f; // 30cm
            static constexpr float FOV = 0.8f; // -> 45 degrees

            State state_;
            rclcpp::Time state_ts_;
            bool is_turning_left;
            bool is_turning_right;

            rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr vel_pub_;
            rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr scan_sub_;
            rclcpp::TimerBase::SharedPtr timer_;

            sensor_msgs::msg::LaserScan::UniquePtr last_scan_; // Stores the last laser scan
    };
}

#endif // FSM_PKG__