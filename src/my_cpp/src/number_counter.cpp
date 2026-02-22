#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
#include "example_interfaces/msg/int64.hpp"
#include "example_interfaces/srv/set_bool.hpp"
using SetBol = example_interfaces::srv::SetBool;

class Number_Counter : public rclcpp::Node
{

public:
    Number_Counter() : Node("number_counter")
    {
        subscriber_ = this->create_subscription<example_interfaces::msg::Int64>(
            "Numbers", 10, std::bind(&Number_Counter::callback, this, std::placeholders::_1));
        RCLCPP_INFO(this->get_logger(), "Number_Counter is Working");

        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number_count", 10); // i need to check
        // the use of that 10

        service_ = this->create_service<SetBol>(
            "reset_counter",
            std::bind(&Number_Counter::reset_callback, this,
                      std::placeholders::_1,
                      std::placeholders::_2));
    };

private:
    void callback(const example_interfaces::msg::Int64::SharedPtr)
    {

        counter_++;
        example_interfaces::msg::Int64 out_msg;
        out_msg.data = counter_;
        publisher_->publish(out_msg);
    }

    void reset_callback(const SetBol::Request::SharedPtr request_,
                        const SetBol::Response::SharedPtr response_)
    {
        if (request_->data)
        {
            counter_ = 0;
            response_->success = true;
            response_->message = "Counter Set to Zero";
        }
        else
        {
            response_->success = false;
            response_->message = "Counter unchanged";
        }
    }

    int counter_ = 0;
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber_;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::Service<SetBol>::SharedPtr service_;
};

int main(int argc, char **argv)
{

    rclcpp::init(argc, argv);
    auto node = std::make_shared<Number_Counter>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}