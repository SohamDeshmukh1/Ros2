# 🤖 Ros2,Gazeebo,Rviz,Tfs,Movelt,ros_control Basic Knowledge Docs

This repo is an Template Repo , Will be Using this in The long term 
by : Soham

---

## 📌 Table of Contents
- ✅ [Description](#description)
- ✅ [Features](#features)
- ✅ [Requirements](#requirements)
- ✅ [Workspace Setup](#workspace-setup)
- [Launch](#launch)


---

## Description
Explain what the project does.

Example:  
This package provides ROS2 nodes to control a robotic arm using publishers, subscribers, and services. It supports both real hardware and Gazebo simulation.

---

## Requirements
- ROS2 Humble / Iron / Jazzy
- Ubuntu As per Latest Need
- colcon
- Python3 / C++

---

## Workspace Setup

### Installations Shown in The Docs Below :

- ROS Installations: [Setup Docs](https://docs.ros.org/)
- Gazebo Installations: [Setup Docs](https://gazebosim.org/docs/harmonic/getstarted/)
- Ros Control: [Setup Docs](https://control.ros.org/jazzy/index.html)


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
Basic XML Template 

```bash
<?xml version="1.0"?>
<robot name="mesh_robot" xmlns:xacro="https://www.ros.org/wiki/xacro">

</robot>
```

