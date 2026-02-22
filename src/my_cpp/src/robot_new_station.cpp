#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
using namespace std::chrono_literals;
class RobotNewsStation: public rclcpp::Node
{
    public :
        RobotNewsStation(): Node("robot_news_station"), robot_name("Robot 1") 
        {

            this->declare_parameter("Robot_name",robot_name);

            robot_name = this->get_parameter("Robot_name").as_string();

            publisher_= this->create_publisher<example_interfaces::msg::String>("Robot_News",10);
            timer_ = this->create_wall_timer(0.5s, std::bind(&RobotNewsStation::Publish, this));
            RCLCPP_INFO(this->get_logger(),"Robot News Station Has been Started");
        }
    private:

        void Publish(){
            auto msg = example_interfaces::msg::String();
            msg.data= std::string("Hi, this is ") + robot_name + std::string(" From The Robot News Station!");
            publisher_->publish(msg);
        };
    std::string robot_name;
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};



int main(int argc, char **argv){

    rclcpp::init(argc,argv);
    auto node = std::make_shared<RobotNewsStation>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}