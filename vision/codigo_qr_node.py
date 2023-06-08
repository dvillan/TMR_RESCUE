#!/usr/bin/env python3

import rclpy
from rclpy.node import Node 
from example_interfaces.msg import Int64
import cv2
from pyzbar.pyzbar import decode 


class CAM(Node):
    def __init__(self):
        super().__init__("qr_node")
        self.cam_channel = 0
        self.get_logger().info("Initializing cams...")
        self.subscriber2 = self.create_subscription(Int64, "switch_cam", self.callback, 10)
        self.subscriber_ = self.create_subscription(Int64, "Emergency_Stop", self.kill_node, 10)
        self.sw_msg = Int64()
        self.sw_msg.data = 0

    def init_camera(self):
        cap.set(cv2.CAP_PROP_FRAME_WIDTH, 920)
        cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
        cap2.set(cv2.CAP_PROP_FRAME_WIDTH, 380)
        cap2.set(cv2.CAP_PROP_FRAME_HEIGHT, 380)
        self.get_logger().info("Camera ON")

        cv2.namedWindow("Rescue", cv2.WINDOW_NORMAL)
        cv2.resizeWindow("Rescue", 920, 480)

        cv2.namedWindow("Reverse Cam", cv2.WINDOW_NORMAL)
        cv2.resizeWindow("Reverse Cam", 640, 480)

    def kill_node(self, msg):
        
        if msg.data == 1:
            cap.release()
            cap2.release()
            cv2.destroyAllWindows()
            rclpy.shutdown()
            self.get_logger().info("Killed")

    def callback(self, msg2):
        self.sw_msg = msg2

        self.get_logger().info(f"{self.cam_channel}")
        self.get_logger().info("Camera switched")

    def show_image(self):
        
        if self.sw_msg.data == 0:
            cv2.destroyWindow("Reverse Cam")
            cv2.imshow('Rescue', img)
            cv2.moveWindow("Rescue", 10, 10)
        else:
            cv2.destroyWindow("Rescue")
            cv2.imshow('Reverse Cam', img2)
            cv2.moveWindow("Reverse Cam", 320, 100)

            
            
def main(args=None):
    rclpy.init(args=args)
    node = CAM()
    global cap, cap2
    cap = cv2.VideoCapture(0)
    cap2 = cv2.VideoCapture(2)
    node.init_camera()
    node.get_logger().info("Camera Ok")

    while rclpy.ok():
        rclpy.spin_once(node, executor=None, timeout_sec=0.05)
        global img, img2
        success, img = cap.read()
        success2, img2 = cap2.read()
        #cv2.putText(img, "QR Read:", (10,120), cv2.FONT_HERSHEY_SIMPLEX,1,(0,255,0), 3)

        for i in decode(img):
            #print(i.type)
            #print(i.data.decode('utf-8'))
            value = i.data.decode('utf-8')
            cv2.putText(img, str(value), (0,240), cv2.FONT_HERSHEY_SIMPLEX,1,(0,255,0), 3)

        node.show_image()
        node.get_logger().info("OK")

        if cv2.waitKey(1) & 0xFF == ord("q"):
            break


if __name__ == "__main__":
    main()