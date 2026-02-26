# 🤖 Ros2,Gazeebo,Rviz,Tfs,Movelt,ros_control Basic Knowledge Docs

All the cmds and Different Templates in 

Example:  
To Create any robot as Required these Basic Cmds and Template will help you in the Long run

---

## 📌 Table of Contents
- ✅ [Description](#description)
- ✅ [Features](#features)
- ✅ [Requirements](#requirements)
- ✅ [Workspace Setup](#workspace-setup)
- [Build](#build)
- [Run](#run)
- [Launch](#launch)
- ✅ [Topics](#topics)
- ✅ [Services](#services)
- ✅ [Parameters](#parameters)
- ✅ [Templates](#templates)
- [Simulation](#simulation)
- [Project Structure](#project-structure)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [License](#license)

---

## Description
Explain what the project does.

Example:  
This package provides ROS2 nodes to control a robotic arm using publishers, subscribers, and services. It supports both real hardware and Gazebo simulation.

---

## Features
- Joint position control
- ROS2 publishers/subscribers
- Service-based commands
- Gazebo / RViz support
- Parameterized configuration

---

## Requirements
- ROS2 Humble / Iron / Jazzy
- Ubuntu As per Latest Need
- colcon
- Python3 / C++
- Dependencies:

---

## Workspace Setup

```bash
# Source ROS2
source /opt/ros/humble/setup.bash

# Create workspace
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws

# Clone repository
git clone <your-repository-url> src/your_repo

# Install dependencies
rosdep install --from-paths src --ignore-src -r -y

# Build workspace
colcon build --symlink-install

# Source workspace
source install/setup.bash
```
---

## Topics

``` bash 
# Tells about current active topics
ros2 topic list

# Topics don’t have to only be one-to-one communication; they can be one-to-many, many-to-one, or many-to-many.

ros2 topic info /topic_name

# Echos Package runtime output
ros2 topic echo /topic_name

# Publish data to a topic
ros2 topic pub /topic_name < msg_type > "{field: value}"
# Example :ros2 topic pub /turtle1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 2.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 1.8}}"

# will return the same list of topics, this time with the topic type appended in brackets:
ros2 topic list -t

#Specifically, what structure of data the message expects.
ros2 interface show geometry_msgs/msg/Twist
```

---

## Services

```bash
#List of all the services currently active in the system
ros2 service list

#To find out the type of a service,
ros2 service type <service_name>

#To see information of a particular service
ros2 service info <service_name>

# You can call a service but you should know its service’s type, and the structure of that type’s arguments
ros2 service call <service_name> <service_type> <arguments>
```

---

## Parameters

```bash
#To display the type and current value of a parameter
ros2 param get <node_name> <parameter_name>

#To change a parameter’s value at runtime
ros2 param set <node_name> <parameter_name> <value>

#You can view all of a node’s current parameter values 
ros2 param dump <node_name>

#Load parameters from a file to a currently running node using the command
ros2 param load <node_name> <parameter_file>
```

## Templates

Basic Cpp Template 

```bash
#include "rclcpp/rclcpp.hpp"

class My_Node : public rclcpp ::Node
{
    public:
        My_Node(): Node("Node_name"){
        }
    private:  
};
int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<My_Node>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

```
Basic Launch Files 

```bash
#Rviz Launch File

<launch>
    <let name ="urdf_path" value ="$(find-pkg-share my_robot_description)/urdf/my_robot.urdf.xacro"/>
    <let name ="rviz_confg" value ="$(find-pkg-share my_robot_description)/rviz/test1.rviz"/>

    <node pkg="robot_state_publisher" exec="robot_state_publisher">
    <param name ="robot_description" value="$(command 'xacro $(var urdf_path)')"/>
    </node>    

    <node pkg="joint_state_publisher_gui" exec="joint_state_publisher_gui"/>

    <node pkg="rviz2" exec="rviz2" args="-d $(var rviz_confg)" output="screen"/>
</launch>
```

```bash
#Gazeebo Launch File 

<launch>
    <let name ="urdf_path" value ="$(find-pkg-share my_robot_description)/urdf/my_robot.urdf.xacro"/>
    <let name ="rviz_confg" value ="$(find-pkg-share my_robot_description)/rviz/test1.rviz"/>

    <node pkg="robot_state_publisher" exec="robot_state_publisher">
        <param name="robot_description" 
                value="$(command 'xacro $(my_robot)')"/>
    </node>

    <include file="$(find-pkg-share ros_gz_sim)/launch/gz_sim.launch.py">
        <args name="gz_args" value="empty.sdf -r"/>
    </include>

    <node pkg="ros_gz_sim" exec="create" args="-topic robot_description"/>
    <node pkg="rviz2" exec="rviz2" args="-d $(var rviz_confg)" output="screen"/>

</launch>
```
