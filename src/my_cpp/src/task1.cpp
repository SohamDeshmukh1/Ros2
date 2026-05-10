#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/msg/stepper_motor.hpp"
using namespace std::chrono_literals;
using StepperMotor = my_robot_interfaces::msg::StepperMotor;

class Task1 : public rclcpp ::Node
{
    public:
        Task1() : Node("motor_control"){
            this->declare_parameter("speed",speed);
            this->declare_parameter("steps",steps);
            this->declare_parameter("dir",dir);
            this->declare_parameter("name",name);
            publish_ = this->create_publisher<StepperMotor>("Stepper_command",10);
            timer_ = this->create_wall_timer(1s,std::bind(&Task1::Publish, this));
            RCLCPP_INFO(get_logger(),"Publishing values");
        }

    private:
    void Publish(){
        auto msg = StepperMotor();
        msg.direction = this->get_parameter("dir").as_bool();
        msg.speed=this->get_parameter("speed").as_double();
        msg.steps=this->get_parameter("steps").as_int();
        msg.name=this->get_parameter("name").as_string();
        publish_->publish(msg);
    }
    float speed{12.6};
    int steps{200};
    bool dir{true};
    std::string name{"motor0"};
    rclcpp::Publisher<StepperMotor>::SharedPtr publish_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Task1>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}