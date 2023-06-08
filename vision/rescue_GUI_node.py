#!/usr/bin/env python3

import rclpy
from tkinter import *
from tkinter import messagebox
from rclpy.node import Node 
from example_interfaces.msg import Int64

GUI_SIZE = "920x480"
FONT_NAME = "Helvetica"
BG_COLOR = "#9E9E9E"

class GUI(Node):
    
    def __init__(self):
        super().__init__("rescue_GUI")
        self.publisher_ = self.create_publisher(Int64, "Emergency_Stop", 10)
        self.publisher2 = self.create_publisher(Int64, "switch_cam", 10)
        self.get_logger().info("Initializing GUI... ")
        self.contador = 1
        # msg2 = Int64() ##
        # msg2.data = 0 ##
        # self.publisher2.publish(msg2) ##
        
    def initialize_GUI(self):
        window = Tk()
        window.title("RBBY-23")
        window.geometry(GUI_SIZE)
        window.geometry("+10+600")
        canvas = Canvas(window, width=920, height=480, bg=BG_COLOR)
        canvas2 = Canvas(window, width=400, height=440, bg=BG_COLOR)
        
        em_image = PhotoImage(file="~/Escritorio/TMR_RESCUE/vision/emergency.png")
        emergency_button = Button(window, image=em_image, highlightthickness=0, bd=0, bg=BG_COLOR, activebackground=BG_COLOR, command=self.emergency_press_callback)
        reverse_cam_button = Button(window, text="Switch Cam", command=self.switch_cam)

        emergency_button.place(bordermode=OUTSIDE, x=470, y=55)
        reverse_cam_button.place(bordermode=OUTSIDE, x=160, y=70)
        canvas.pack()

        em_label = Label(text="EMERGENCY BUTTON", bg=BG_COLOR, font=(FONT_NAME, 20, "bold"))
        em_label.place(bordermode=OUTSIDE, x=520, y=10)

        canvas2.place(bordermode=OUTSIDE, x=20, y=20)
        canvas2.create_text(195, 25, text="CURRENT ROBOT STATE",fill="white", font=(FONT_NAME, 		 16, "bold"))
        #canvas2.create_text(120, 70, text="All systems working well... ",fill="white",  font=(FONT_NAME, 12, "bold"))
        #canvas2.create_text(240, 70, text="✔", fill="GREEN", font=(FONT_NAME, 18, "bold"))
        rbby = PhotoImage(file="~/Escritorio/TMR_RESCUE/vision/robot.png")
        canvas2.create_image(155, 255, image=rbby)
        
        window.mainloop()
     
    def emergency_press_callback(self):
        msg = Int64()
        msg.data = 1 
        self.publisher_.publish(msg)
        messagebox.showwarning(title="Warning", message="All processes have been stopped")
         
    def switch_cam(self):
        msg2 = Int64()
        self.contador += 1
        if self.contador %2 == 0:
            msg2.data = 1   ## Camara Trasera 
        else:
            msg2.data = 0   ## Camara frontal 

        self.publisher2.publish(msg2)

           


def main(args=None):
    rclpy.init(args=args)
    node = GUI()
    node.initialize_GUI()
    rclpy.spin(node)
    rclpy.shutdown()
    
if __name__ == "__main__":
    main()
    

