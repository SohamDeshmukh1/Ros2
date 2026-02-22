
cmake_minimum_required(VERSION 3.8)
project(my_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(my_robot_interfaces REQUIRED)
find_package(turtlesim REQUIRED)
find_package(geometry_msgs REQUIRED)


add_executable(cpp_node src/my_first.cpp)
ament_target_dependencies(cpp_node rclcpp)

add_executable(robot_new_station src/robot_new_station.cpp )
# the name above is the name of the Executable and below is the name of the node
ament_target_dependencies(robot_new_station rclcpp example_interfaces )

add_executable(smartphone src/smartphone.cpp)
ament_target_dependencies(smartphone rclcpp example_interfaces)

add_executable(number_publisher src/number_publisher.cpp)   
ament_target_dependencies(number_publisher rclcpp example_interfaces)

add_executable(number_counter src/number_counter.cpp)   
ament_target_dependencies(number_counter rclcpp example_interfaces)

add_executable(add_two_server src/add_two_server.cpp)   
ament_target_dependencies(add_two_server rclcpp example_interfaces)

add_executable(add_two_int_client src/add_two_int_client.cpp)   
ament_target_dependencies(add_two_int_client rclcpp example_interfaces)

add_executable(add_two_client_oop src/add_two_client_oop.cpp)   
ament_target_dependencies(add_two_client_oop rclcpp example_interfaces)

add_executable(hw_status_publisher src/hardware_status_publisher.cpp)   
ament_target_dependencies(hw_status_publisher rclcpp my_robot_interfaces)

add_executable(Led_node src/Led_node.cpp)   
ament_target_dependencies(Led_node rclcpp my_robot_interfaces)

add_executable(Battery_node src/Battery_node.cpp)   
ament_target_dependencies(Battery_node rclcpp my_robot_interfaces example_interfaces)

add_executable(Turtle_Spawn src/Turtle_Spawn.cpp)   
ament_target_dependencies(Turtle_Spawn rclcpp my_robot_interfaces)

add_executable(Turtle_Controller src/Turtle_Controller.cpp)   
ament_target_dependencies(Turtle_Controller rclcpp turtlesim geometry_msgs my_robot_interfaces)

install(TARGETS
  Turtle_Spawn
  Turtle_Controller
  cpp_node 
  Battery_node
  number_publisher
  add_two_int_client
  hw_status_publisher
  add_two_client_oop
  number_counter
  add_two_server
  robot_new_station
  smartphone
  Led_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()

