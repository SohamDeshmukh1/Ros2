#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class NumbersPublisher : public rclcpp::Node
{
public:
    NumbersPublisher() : Node("NumberPublisher"), counter_(0)
    {

        this->declare_parameter("counter_", 2);
        this->declare_parameter("timer_period", 1.0);

        // The name given in the bracket is like created for us it makes meaning only for parameter
        // it does not play the role in actual variables we have declared

        counter_ = this->get_parameter("counter_").as_int();
        double timer_period = this->get_parameter("timer_period").as_double();

        // the name here double timer_period and Counter_ is imp as they contain the value and the name inside get_parameter is like
        // from which declare parameter we need to fetch the data for this variable
        // just crosschescking we can see
        Param_callback_ = this->add_post_set_parameters_callback(std::bind(&NumbersPublisher::Parametercall,
                                                                           this, std::placeholders::_1));
        publish_ = this->create_publisher<example_interfaces::msg::Int64>("Numbers", 10);
        timer_ = this->create_wall_timer(std::chrono::duration<double>(timer_period), std::bind(&NumbersPublisher::Publish, this));
        RCLCPP_INFO(this->get_logger(), "I am a Number Publisher");
    }

private:
    void Parametercall(const std::vector<rclcpp::Parameter> & paramaters)
    {
        for(const auto & param: paramaters){
            if(param.get_name()=="counter_"){
                counter_ = param.as_int();
            }
        }
    }
    // some new info BRUUHHHHHHHHHHHHHHHhh

    void Publish()
    {
        auto msg = example_interfaces::msg::Int64();
        msg.data = counter_;
        publish_->publish(msg);
    };
    int counter_;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publish_;
    rclcpp::TimerBase::SharedPtr timer_;
    PostSetParametersCallbackHandle::SharedPtr Param_callback_;
};

int main(int argc, char **argv)
{
    rclcpp ::init(argc, argv);
    auto node = std::make_shared<NumbersPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}