#!/usr/bin/env python3

import serial
import rclpy

from rclpy.node import Node
from geometry_msgs.msg import Twist

class CmdVelToSerial(Node):

    def __init__(self):
        super().__init__('cmd_vel_to_serial')

        self.serial = serial.Serial('/dev/ttyACM0', 115200, timeout=1)

        self.subscription = self.create_subscription(
            Twist,
            '/cmd_vel',
            self.cmd_callback,
            10
        )

        self.get_logger().info("Connected to ESP32")

    def cmd_callback(self, msg):

        linear = msg.linear.x
        angular = msg.angular.z

        data = f"{linear:.2f},{angular:.2f}\n"

        self.serial.write(data.encode())

        self.get_logger().info(f"Send: {data.strip()}")

def main(args=None):

    rclpy.init(args=args)

    node = CmdVelToSerial()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass

    node.serial.close()
    node.destroy_node()

    rclpy.shutdown()

if __name__ == '__main__':
    main()
