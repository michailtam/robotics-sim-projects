#include "fsm_pkg/fsm_node.hpp"


namespace fsm_pkg
{
    FSM_node::FSM_node() : Node("fsm_node"), state_(State::FORWARD)
    {   
        scan_sub_ = this->create_subscription<sensor_msgs::msg::LaserScan>("input_scan", 
            rclcpp::SensorDataQoS(), std::bind(&FSM_node::laserscan_callback, this, _1));

        vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("output_vel", 10);

        // This timer is neccessary to execute the control cycle in a specific time interval
        timer_ = this->create_wall_timer(50ms, std::bind(&FSM_node::control_cycle, this));
        state_ts_ = now(); // Initializes the first time state

        is_turning_left = is_turning_right = false; // Flags which determine to which side the robot turns
    }

    void FSM_node::laserscan_callback(sensor_msgs::msg::LaserScan::UniquePtr msg)
    {
        last_scan_ = std::move(msg); // Saves the last laserscan
    }

    void FSM_node::control_cycle()
    {
        // If there is no saved laserscan
        if (last_scan_ == nullptr) 
            return;
        
        geometry_msgs::msg::Twist out_vel;
        
        // Determines which state to execute
        switch (state_) 
        {
            case State::FORWARD:
                out_vel.linear.x = SPEED_LINEAR;    
                if (check_forward_2_stop())
                    go_state(State::STOP); 
                if (check_forward_2_back()) 
                    go_state(State::BACK);
                break;

            case State::BACK:
                out_vel.linear.x = -SPEED_LINEAR;
                if (check_back_2_turn())
                    go_state(State::TURN);
                break;

            case State::TURN:
                {
                    // Checks if there is an obstacle on the left, front or the right side
                    int obstacle_at = check_for_obstacle();
                    if (obstacle_at == 1 && !is_turning_left && !is_turning_right)
                        is_turning_right = true;
                    else if (obstacle_at == 2 && !is_turning_left && !is_turning_right)
                        is_turning_left = true;

                    if (is_turning_left) {
                        out_vel.angular.z = SPEED_ANGULAR;
                    } else if (is_turning_right) {    
                        out_vel.angular.z = -SPEED_ANGULAR;
                    }

                    if (check_turn_2_forward()) {
                        is_turning_left = is_turning_right = false;
                        go_state(State::FORWARD);
                    }
                }
                break;

            case State::STOP:
                if (check_stop_2_forward())
                    go_state(State::FORWARD);
                break;
        }
        vel_pub_->publish(out_vel);
    }

    void FSM_node::go_state(State new_state)
    {
        state_ = new_state; // Saves the new state
        state_ts_ = now();  // Saves the new time of the state
    }

    bool FSM_node::check_forward_2_back()
    {
        // Moves back when an obstacle gets detected at a specific distance by the front laser read
        size_t pos = last_scan_->ranges.size() / 2;
        int center_pos = pos / 2;
        int angle_pos = (FOV / last_scan_->angle_increment) / 2; // The laserscan position of the first angle quarter

        // Prepares the array for slicing
        std::valarray<double> scans(last_scan_->ranges.size());
        for (int i=0; i<=last_scan_->ranges.size()-1; i++) {
            scans[i] = last_scan_->ranges[i];
        }
        std::valarray<double> left_scan = scans[std::slice(center_pos+1, (center_pos + angle_pos), 1)];
        std::valarray<double> right_scan = scans[std::slice((center_pos - angle_pos), center_pos-1, 1)];

        if (left_scan.min() <= OBSTACLE_DISTANCE) {
            return true;
        } 
        if (right_scan.min() <= OBSTACLE_DISTANCE) {
            return true;
        }
        return false;
    }

    bool FSM_node::check_forward_2_stop()
    {
        // Returns true if there is no sensor reading for a specific time (i.e. SCAN_TIMEOUT)
        // while moving forward
        auto elapsed = now() - rclcpp::Time(last_scan_->header.stamp);
        return elapsed > SCAN_TIMEOUT;
    }

    bool FSM_node::check_back_2_turn()
    {
        // Moves back for a specific time
        return (now() - state_ts_) > BACKING_TIME;
    }

    bool FSM_node::check_turn_2_forward()
    {
        // Turns for a specific time
        return (now() - state_ts_) > TURNING_TIME;
    }

    bool FSM_node::check_stop_2_forward()
    {
        // Moves forward if there are sensor readings available
        auto elapsed = now() - rclcpp::Time(last_scan_->header.stamp);
        return elapsed < SCAN_TIMEOUT;
    }

    double FSM_node::rad_2_degree(double radians)
    {
        double pi = 3.14159;
        return(radians * (180 / pi));
    }

    int FSM_node::check_for_obstacle()
    {
        // Determines if on the left or right diagonal of the robot is an obstacle, and returns the side of the observed obstacle
        // -1: no obstacle, 1: obstacle on the left, 2: obstacle on the right
        unsigned int scan_num = (last_scan_->angle_max - last_scan_->angle_min) / last_scan_->angle_increment;
        int center_pos = scan_num/2;
        int angle_pos = (FOV / last_scan_->angle_increment) / 2; // The laserscan position of the first angle quarter

        // Prepares the array for slicing
        std::valarray<double> scans(last_scan_->ranges.size());
        for (int i=0; i<=last_scan_->ranges.size()-1; i++) {
            scans[i] = last_scan_->ranges[i];
        }
        std::valarray<double> left_scan = scans[std::slice(center_pos+1, (center_pos + angle_pos), 1)];
        std::valarray<double> right_scan = scans[std::slice((center_pos - angle_pos), center_pos-1, 1)];

        double left_dist = left_scan.sum(); // Gets the min value of the left side scans
        double right_dist = right_scan.sum(); // Gets the min value of the right side scans

        // Returns the side to turn. The side to turn gets determined by the highest sum of the laserscan quarter
        // For example, if the left sum is lower than the right one, the robot turns to the right
        if (!std::isinf(left_dist) && !std::isinf(right_dist)) 
        {
            if (left_dist < right_dist) {
                return 1;
            } else if(right_dist < left_dist) {
                return 2;
            }
        }
        return -1;
    }
}
