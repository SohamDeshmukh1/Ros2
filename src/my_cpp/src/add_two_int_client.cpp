#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"
using namespace std::chrono_literals;

// class Addtwointclient : public rclcpp::Node{
    // rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_;
// };

int main(int argc,char **argv){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<rclcpp::Node>("Add_two_int_client");
    auto client = node ->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
    while (!client ->wait_for_service(2s)){
        RCLCPP_WARN(node->get_logger(),"Waiting for the server ...");
    };
    
    auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
    request -> a = 10;
    request -> b = 40;
    
    auto future = client ->async_send_request(request);
    rclcpp::spin_until_future_complete(node, future);

    auto response = future.get();
    RCLCPP_INFO(node -> get_logger(),"%d + %d = %d", (int)request->a, (int)request->b, (int)response->sum);
                      
    rclcpp::shutdown();
    return 0;
}