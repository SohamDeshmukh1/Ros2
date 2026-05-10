#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/msg/stepper_motor.hpp"
using StepperMotor = my_robot_interfaces::msg::StepperMotor;

class Task1_2 : public rclcpp ::Node
{
    public:
       Task1_2(): Node("Motor_Listner"){
        subscribe_ = this->create_subscription <StepperMotor>("Stepper_command",10,std::bind
            (&Task1_2::Subscribe,this,std::placeholders::_1));
       }
    private:
       void Subscribe(const StepperMotor::SharedPtr msg){
        RCLCPP_INFO(this-> get_logger(),
                "\n Name:%s \n Speed: %.2f \n Steps: %d \n Direction: %d",
                msg->name.c_str(),
                msg->speed,
                msg->steps,
                msg->direction);
       }

    rclcpp::Subscription<StepperMotor>::SharedPtr subscribe_;
    rclcpp::TimerBase::SharedPtr publish_;

};

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Task1_2>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}