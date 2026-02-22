#!/usr/bin/env python3 
import rclpy
from rclpy.node import Node

class HelloWorldNode(Node):
    def __init__(self):
        super().__init__('hello_world')  # Node name
        self.get_logger().info("Hello ROS 2 World!")  # Print once
        # Optional: Timer to print repeatedly
        self.timer = self.create_timer(1.0, self.timer_callback)
        self.counter = 0

    def timer_callback(self):
        self.get_logger().info(f"Hello World count: {self.counter}")
        self.counter += 1

def main(args=None):
    rclpy.init(args=args)
    node = HelloWorldNode()
    rclpy.spin(node)  # Keep node alive
    rclpy.shutdown()

if __name__ == '__main__':
    main()
