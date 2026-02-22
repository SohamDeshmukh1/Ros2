#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include "rclcpp/rclcpp.hpp"
#include "turtlesim/srv/spawn.hpp"
#include "turtlesim/msg/pose.hpp"
#include "my_robot_interfaces/msg/turtle_list.hpp"
#include "my_robot_interfaces/msg/turtle_info.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/srv/kill.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

class Turtle_Controller : public rclcpp ::Node
{
public:
    Turtle_Controller() : Node("Turtle_Controller")
    {
        subscribe_ = this->create_subscription<my_robot_interfaces::msg::TurtleList>("alive_turtle", 5,
                                                                                     std::bind(&Turtle_Controller::Subscriber, this, _1));
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        position_ = this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose", 1,
                                                                    std::bind(&Turtle_Controller::Target, this, _1));
        client_ = this->create_client<turtlesim::srv::Spawn>("/spawn");
        killclient_ = this->create_client<turtlesim::srv::Kill>("/kill");
        while (!client_ && !killclient_->wait_for_service(3s))
        {
            RCLCPP_INFO(this->get_logger(), "Waiting for Server");
        }
    }

private:
    void Subscriber(const my_robot_interfaces::msg::TurtleList::SharedPtr msg)
    {
        turtles_ = msg->turtle_list;
        // Storing them in a Private vector variable below
        Spawner(turtles_);
    }
    void Spawner(const std::vector<my_robot_interfaces::msg::TurtleInfo> &turtles)
    {
        for (const auto &t : turtles)
        {
            auto request = std::make_shared<turtlesim::srv::Spawn::Request>();
            request->name = t.name;
            request->x = t.x;
            request->y = t.y;
            request->theta = t.theta;
            // Sending request to Turtlesim Server Service
            auto future = client_->async_send_request(request);
        }
    }
    void Target(const turtlesim::msg::Pose::SharedPtr msg)
    {
        // Getting Default Position of Turtle Spawned by System here and Processing it to find nearest
        // Turtle based on its own position
        double min_dist = 1e9;
        double dx = 0.0;
        double dy = 0.0;
        std::string name;
        // we can also put a garbage value here
        if (turtles_.empty())
        {
            return;
        }

        for (const auto &t : turtles_)
        {
            double temp_dx = t.x - msg->x;
            double temp_dy = t.y - msg->y;
            std::string temp_name = t.name;
            double dist = std::sqrt(temp_dx * temp_dx + temp_dy * temp_dy); // Distance Calculation
            // These Formulas are Copied from Internet and Chat GPT i will further Study them too

            // Calculating nearest turtle distance
            if (dist < min_dist)
            {
                min_dist = dist;
                nearest_turtle = t;
                dx = temp_dx;
                dy = temp_dy;
                name = temp_name;
            }
        }
        double target_angle = std::atan2(dy, dx);       // Target Angle Calculation
        double angle_error = target_angle - msg->theta; // mgs->thea = Current Angle of Rotation
        Movement(min_dist, angle_error, name);
    }
    void Movement(double distance, double angle, std::string name)
    {
        geometry_msgs::msg::Twist cmd;

        cmd.linear.x = std::clamp(3.0 * distance, 0.0, 2.0); // This is for the Distance
        cmd.angular.z = std::clamp(4.0 * angle, -4.0, 4.0); // proportional rotation
        publisher_->publish(cmd);
        if (distance < 0.5)
        {
            // this code is taken from gpt i need to study a bit
            geometry_msgs::msg::Twist stop; // values by default are 0 in ros theres no garbage values in them
            publisher_->publish(stop);

            RCLCPP_INFO(this->get_logger(), "Killing turtle: %s", name.c_str());
            killturtle(name);

            turtles_.erase(
                std::remove_if(turtles_.begin(), turtles_.end(),
                               [&](const auto &t)
                               { return t.name == name; }),
                turtles_.end());
            // The vectors i need to study them taking help from gpt for that
        }
    }
    void killturtle(const std::string &name)
    {
        auto request = std::make_shared<turtlesim::srv::Kill::Request>();
        request->name = name;
        auto future = killclient_->async_send_request(request);
    }

    rclcpp::Subscription<my_robot_interfaces::msg::TurtleList>::SharedPtr subscribe_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    my_robot_interfaces::msg::TurtleInfo nearest_turtle;
    std::vector<my_robot_interfaces::msg::TurtleInfo> turtles_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr position_;
    rclcpp::Client<turtlesim::srv::Spawn>::SharedPtr client_;
    rclcpp::Client<turtlesim::srv::Kill>::SharedPtr killclient_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Turtle_Controller>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}