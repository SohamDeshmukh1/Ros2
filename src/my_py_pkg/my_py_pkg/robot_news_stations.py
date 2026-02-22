#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import String

class  RobotNewsStation(Node):
    def __init__(self):
        super().__init__("robot_news_station")
        self.publishers_ = self.create_publisher(String,"robo_news",10)

def main(args=None):
    rclpy.init(args=args)
    node= RobotNewsStation()
    rclpy.spin(node)
    rclpy.shutdown() 
if __name__ == "__main__":
    main()
