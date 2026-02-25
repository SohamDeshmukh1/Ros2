# 🤖 Ros2,Gazeebo,Rviz,Tfs,Movelt,ros_control Basic Knowledge Docs

Short one-line summary of your robot / package.

Example:  
To Create any robot as Required these Basic Cmds and Template will help you in the Long run

---

## 📌 Table of Contents
- [Description](#description)
- [Features](#features)
- [Requirements](#requirements)
- [Workspace Setup](#workspace-setup)
- [Build](#build)
- [Run](#run)
- [Launch](#launch)
- [Topics](#topics)
- [Services](#services)
- [Parameters](#parameters)
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
## Topics

``` bash 
# Tells about current active topics
ros2 topic list
```


``` bash 
# Tells info about the package
ros2 topic info /topic_name
```

``` bash 
# Echos Package runtime output
ros2 topic echo /topic_name
```


```bash
# Publish data to a topic
ros2 topic pub /topic_name < msg_type > "{field: value}"
```

Example:

```bash
ros2 topic pub /chatter std_msgs/msg/String "{data: 'Hello ROS 2'}"
```

```bash
ros2 topic list -t
# will return the same list of topics, this time with the topic type appended in brackets:
```
Example:

```bash
ros2 topic list -t
/parameter_events [rcl_interfaces/msg/ParameterEvent]
/rosout [rcl_interfaces/msg/Log]
/turtle1/cmd_vel [geometry_msgs/msg/Twist]
/turtle1/color_sensor [turtlesim/msg/Color]
/turtle1/pose [turtlesim/msg/Pose]
```
