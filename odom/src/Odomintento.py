#!/usr/bin/env python
import serial
import math
from math import sin, cos, pi

import rospy
import tf
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Point, Pose, Quaternion, Twist, Vector3

rospy.init_node('odometry_publisher') 

odom_pub = rospy.Publisher("odom", Odometry, queue_size=50)
odom_broadcaster = tf.TransformBroadcaster()

x = 0.0
y = 0.0
th = 0.0

vx =0 
vy = 0
vth =0

current_time = rospy.Time.now()
last_time = rospy.Time.now()

r = rospy.Rate(1.0)
while not rospy.is_shutdown():
    current_time = rospy.Time.now()
    
    if ser.in_waiting > 0:
        data = ser.readline().decode().strip()
        values = data.split(',')

        if len(values) == 3:
            try:
                vx = float(values[0])
                vth = float(values[1])
                yaw = float(values[2])
            
                # Calculamos odometria dadas las velocidades del robor
                dt = (current_time - last_time).to_sec()
                delta_x = (vx * cos(th)) * dt
                delta_y = (vx * sin(th)) * dt
                delta_th = vth * dt

                x += delta_x
                y += delta_y
                th += delta_th

                odom_quat = tf.transformations.quaternion_from_euler(0, 0, th)

                # Publicamos la transformada en tf
                odom_broadcaster.sendTransform(
                    (x, y, 0.),
                    odom_quat,
                    current_time,
                    "base_link",
                    "odom"
                )

                # Publicamos la odometrua en ROS
                odom = Odometry()
                odom.header.stamp = current_time
                odom.header.frame_id = "odom"

                # Establecemos la posicion
                odom.pose.pose = Pose(Point(x, y, 0.), Quaternion(*odom_quat))

                # Establecemos la velocidad
                odom.child_frame_id = "base_link"
                odom.twist.twist = Twist(Vector3(vx, vy, 0), Vector3(0, 0, vth))

                # Publicamos el mensaje
                odom_pub.publish(odom)

                last_time = current_time
                r.sleep()