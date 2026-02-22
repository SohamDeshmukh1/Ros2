#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/msg/hardware_status.hpp"
using namespace std::chrono_literals;

class hardware_status_publisher: public rclcpp::Node
{
    public :
        hardware_status_publisher(): Node("hardware_status_publisher")
        {
            publisher_ = this->create_publisher<my_robot_interfaces::msg::HardwareStatus>(
                "hardware_status", 10);  
            timer_ = this->create_wall_timer(
                1s, std::bind(&hardware_status_publisher::publishHardwareStatus,this));
                RCLCPP_INFO(this->get_logger(),"Hardware status Published");      
        }
    private:
        void publishHardwareStatus(){
            auto msg = my_robot_interfaces::msg::HardwareStatus();
            msg.temperature = 57.2;
            msg.are_motor_ready = false;
            msg.debug_message = "Motors too hot";
            publisher_ ->publish(msg);
        }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<my_robot_interfaces::msg::HardwareStatus>::SharedPtr publisher_;
};



int main(int argc, char **argv){

    rclcpp::init(argc,argv);
    auto node = std::make_shared<hardware_status_publisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}