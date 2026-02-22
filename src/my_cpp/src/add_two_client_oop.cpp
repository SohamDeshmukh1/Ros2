#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"
using namespace std::chrono_literals;
using Addtwoints = example_interfaces::srv::AddTwoInts;
using namespace std::placeholders;

class AddTwoClientOop : public rclcpp ::Node
{
public:
    AddTwoClientOop() : Node("add_two_client_oop")
    {
        client_ = this->create_client<Addtwoints>("add_two_ints");
    }

    void callAddtwoint(int a, int b)
    {
        while (!client_->wait_for_service(2s))
        {
            RCLCPP_WARN(this->get_logger(), "Waiting for the server ...");
        };

        auto request = std::make_shared<Addtwoints::Request>();
        request->a = a;
        request->b = b;

        client_ -> async_send_request(request ,std::bind(&AddTwoClientOop::callback, this ,_1) );
    }

private:
    void callback(rclcpp::Client<Addtwoints>::SharedFuture future)
    {
        auto response = future.get();
        RCLCPP_INFO(this->get_logger(),"sum : %d", (int)response->sum);
    }
    rclcpp::Client<Addtwoints>::SharedPtr client_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    int a , b;
    std::cout<< "Enter values you want to add \n Value 1 :";
    std::cin>>a;
    std::cout<<"Value 2:";
    std::cin>>b;
    auto node = std::make_shared<AddTwoClientOop>();
    node ->callAddtwoint(a,b);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}