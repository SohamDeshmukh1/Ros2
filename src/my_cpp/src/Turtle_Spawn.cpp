#include <cstdlib>
#include <ctime>
#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/msg/turtle_info.hpp"
#include "my_robot_interfaces/msg/turtle_list.hpp"
using namespace std::chrono_literals;
using namespace std::placeholders;

class Turtle_Spawn : public rclcpp ::Node
{
    public:
        Turtle_Spawn():Node("Turtle_Spawner"){

            publish_ = this->create_publisher<my_robot_interfaces::msg::TurtleList>("alive_turtle",1);
            timer_ = this->create_wall_timer(5s,std::bind(&Turtle_Spawn::PublishValue,this));
            
        }
    private:
       void PublishValue(){
            auto msg = my_robot_interfaces::msg::TurtleInfo();
            auto insert = my_robot_interfaces::msg::TurtleList();
            counter_ ++;
            msg.name = "enemy"+std::to_string(counter_);
            RCLCPP_INFO(this->get_logger(),"name is %s",msg.name.c_str());
            msg.x = 1.0 +((double)rand()/RAND_MAX) * 10.0;
            msg.y = 1.0 +((double)rand()/RAND_MAX) * 10.0; 
            msg.theta = 1.0 +((double)rand()/RAND_MAX) * 10.0; 
            insert.turtle_list.push_back(msg);
            publish_ -> publish(insert);             
       }
    
    rclcpp::Publisher<my_robot_interfaces::msg::TurtleList>::SharedPtr publish_;
    rclcpp::TimerBase::SharedPtr timer_;
    int counter_ = 1 ;
};

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Turtle_Spawn>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}