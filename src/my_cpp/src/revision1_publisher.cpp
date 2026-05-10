#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
using namespace std::chrono_literals;
class Revision1 : public rclcpp ::Node
{
    public:
    Revision1() : Node("Revision1"){
        publish_ = this -> create_publisher<example_interfaces::msg::String>("Revision1",10);
       timer_ = this->create_wall_timer(0.5s,std::bind(&Revision1::Publish,this));
    }
    private:

    void Publish(){
        auto msg = example_interfaces::msg::String();
        msg.data = std::string("Hi this is") + robot_name;
        publish_->publish(msg);
    }

    std::string robot_name{"Robot1"};
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publish_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Revision1>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}