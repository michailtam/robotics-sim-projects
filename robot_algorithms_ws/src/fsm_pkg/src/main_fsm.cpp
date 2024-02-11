#include "rclcpp/rclcpp.hpp"
#include "fsm_pkg/fsm_node.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto bumpgo_node = std::make_shared<fsm_pkg::FSM_node>();

    rclcpp::spin(bumpgo_node);
    rclcpp::shutdown();

    return 0;
}