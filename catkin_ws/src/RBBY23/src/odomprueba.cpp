#include "ros/ros.h"
#include <geometry_msgs/Vector3.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

ros::Time current_time, last_time;
double x_;
double y_;
double yaw_;
double vel_;//Velocidad del robot
double Acker_;// Angulo de Ackerman
double wheelbase_;//Distancia del rear al front
double track_;//Distancia de llanta izquierda a llanta derecha



void WheelCallback(const geometry_msgs::Vector3::ConstPtr& ticks)
{
 vel_ = ticks->x;
 Acker_ = ticks->y;
 double dt = (current_time - last_time).toSec();

 double delta = atan2(track_ * tan( Acker_),wheelbase_);
 double x = cos(yaw_)*vel_*dt;
 double y = sin(yaw_)*vel_*dt;
 double th = vel_/wheelbase_*tan(delta)*dt;
 
 x_ += cos(yaw_ + delta) * x - sin(yaw_ + delta) * y;
 y_ += sin(yaw_ + delta) * x + cos(yaw_ + delta) * y;
 yaw_ += th;
    
}


int main(int argc, char **argv)
{
 ros::init(argc, argv, "odometry_publisher");
    
  ros::NodeHandle n;
  ros::Subscriber sub=n.subscribe("pos",100,WheelCallback);
  ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 100);
  tf::TransformBroadcaster odom_broadcaster;
  ros::Time current_time, last_time;
  current_time = ros::Time::now();
  last_time = ros::Time::now();

  ros::Rate r(1.0);
  while(n.ok()){

    ros::spinOnce();               // check for incoming messages
    current_time = ros::Time::now();

    //since all odometry is 6DOF we'll need a quaternion created from yaw
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(yaw_);

    //first, we'll publish the transform over tf
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    odom_trans.transform.translation.x = x_;
    odom_trans.transform.translation.y = y_;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    //send the transform
    odom_broadcaster.sendTransform(odom_trans);

    //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";

    //set the position
    odom.pose.pose.position.x = x_;
    odom.pose.pose.position.y = y_;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    //set the velocity
    odom.child_frame_id = "base_link";
    odom.twist.twist.linear.x = vel_;
    odom.twist.twist.linear.y = 0;
    odom.twist.twist.angular.z =Acker_;

    //publish the message
    odom_pub.publish(odom);

    last_time = current_time;
    r.sleep();
  }
}