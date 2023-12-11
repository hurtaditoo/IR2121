#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include <iostream>
#include <cstdlib>

using namespace std::chrono_literals;

void topic_callback(const nav_msgs::msg::Odometry::SharedPtr msg)
{
  std::cout << msg->data << std::endl;
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

  while (rclcpp::ok()) {
    message.pose.position.x = x;
    message.pose.position.y = y;
    
    publisher->publish(message);
    rclcpp::spin_some(node);
    loop_rate.sleep();
  }
  rclcpp::shutdown();
  return 0;
}

