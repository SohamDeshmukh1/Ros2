#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"


using namespace std::placeholders;
using AddTwoInts = example_interfaces::srv::AddTwoInts;

class AddTwoNum : public rclcpp::Node
{

public:
    AddTwoNum() : Node("Add_two")
    {
        server_ = this ->create_service<AddTwoInts>("add_two_ints"
            ,std::bind(&AddTwoNum::AddTwoNumbers,this , _1 , _2 ));
            RCLCPP_INFO(this-> get_logger(), "Add two number service has been started ");
    };

private:
    void AddTwoNumbers(const AddTwoInts::Request::SharedPtr request,
                       const AddTwoInts::Response::SharedPtr response)
                       {
                        response->sum = request ->a + request ->b;
                        RCLCPP_INFO(this -> get_logger(),"%d + %d = %d", (int)request->a, (int)request->b, (int)response->sum);
                       }

    rclcpp::Service<AddTwoInts>::SharedPtr server_;
};


int main(int argc, char **argv){

    rclcpp::init(argc,argv);
    auto node = std::make_shared<AddTwoNum>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}