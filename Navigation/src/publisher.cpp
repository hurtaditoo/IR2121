#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include <iostream>
#include <cstdlib>

using namespace std::chrono_literals;

double lodom, wodom;
void topic_callback(const nav_msgs::msg::Odometry::SharedPtr msg)
{
   lodom = msg->twist.twist.linear.x;
   wodom = msg->twist.twist.angular.z;
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("publisher");
  auto publisher = node->create_publisher<geometry_msgs::msg::PoseStamped>("goal_pose", 10);
  auto subscription = node->create_subscription<nav_msgs::msg::Odometry>("odom", 10, topic_callback);
  geometry_msgs::msg::PoseStamped message;
  
  rclcpp::WallRate loop_rate(500ms);
    
  double x=-1, y=3;
  int flag = 0;	// Condición de parar
  while (rclcpp::ok() && flag == 0) {
    message.pose.position.x = x;
    message.pose.position.y = y;
    
    publisher->publish(message);
    
    if ((std::abs(lodom) < 0.05) && (std::abs(wodom) < 0.05))
    	flag = 1;
    
    rclcpp::spin_some(node);
    loop_rate.sleep();

  }
  rclcpp::shutdown();
  return 0;
}

