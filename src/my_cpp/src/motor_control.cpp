#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
using namespace std::chrono_literals;

class Motor_Control : public rclcpp::Node
{
    public:
    Motor_Control() : Node("motor_1")
    {
        publish_ = this->create_publisher<std_msgs::msg::Int32>("motor_1",10);
        timer_ = this->create_wall_timer(1.0s,std::bind(&Motor_Control::Publish, this));
        RCLCPP_INFO(this->get_logger(),"Info Getting Published");
    }

    private:
    void Publish(){
        auto msg = std_msgs::msg::Int32();
        msg.data = 1;
        publish_ -> publish(msg);
        RCLCPP_INFO(this->get_logger(), "Published motor_enable = %d", msg.data);
    }

    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publish_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv){

    rclcpp::init(argc, argv);
    auto node = std::make_shared<Motor_Control>();
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}