#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/msg/let_state_array.hpp"
#include "my_robot_interfaces/srv/set_led.hpp"

using namespace std::chrono_literals;

// this program is like u can control only 1 led at a time we will need the use of an array for multiple led controls

class Led_node : public rclcpp::Node
{
public:
    Led_node() : Node("Led_node")
    {

        this->declare_parameter<std::vector<int64_t>>("Led_State", std::vector<int64_t>{0, 0, 0});
// i need to do this here std::vector<int64_t>{0, 0, 0} cause its ros safety 
// what if the value is not declared below so its like a cross check point for stuff like that
        led_state = this->get_parameter("Led_State").as_integer_array();
    
        publisher_ = this->create_publisher<my_robot_interfaces::msg::LetStateArray>("let_panel_state", 10);
        RCLCPP_INFO(this->get_logger(), "Led node is now publishing");
        timer_ = this->create_wall_timer(5s, std::bind(&Led_node::Publishing, this));

        service_ = this->create_service<my_robot_interfaces::srv::SetLed>("set_led",
                                                                          std::bind(&Led_node::Led_Callback, this,
                                                                                    std::placeholders::_1,
                                                                                    std::placeholders::_2));
    }
private:
    void Publishing()
    {
        auto msg = my_robot_interfaces::msg::LetStateArray();
        msg.led_status = led_state;
        publisher_->publish(msg);
    }

    void Led_Callback(const my_robot_interfaces::srv::SetLed::Request::SharedPtr request_,
                      const my_robot_interfaces::srv::SetLed::Response::SharedPtr response_)
    {

        int led = request_->led_number;
        int state = request_->state;

        if (led < 0 || led >= static_cast<int>(led_state.size()))
        {
            response_->led_ok = false;
            return; // i learned from gpt i was not applying Return here i also need to stop
                    // didnt thought about that
        }
        if (state != 0 && state != 1)
        {
            response_->led_ok = false;
            return;
        }

        led_state[led] = state;
        response_->led_ok = true;
        Publishing();
    }
    rclcpp::TimerBase::SharedPtr timer_;
    std::vector<int64_t> led_state;
    rclcpp::Publisher<my_robot_interfaces::msg::LetStateArray>::SharedPtr publisher_;
    rclcpp::Service<my_robot_interfaces::srv::SetLed>::SharedPtr service_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Led_node>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}