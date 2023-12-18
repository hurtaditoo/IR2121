#include <chrono>
#include <iostream>
#include <cstdlib>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "tf2_ros/transform_listener.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

using namespace std::chrono_literals;

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("publisher");
  auto publisher = node->create_publisher<geometry_msgs::msg::PoseStamped>("goal_pose", 10);
    
  geometry_msgs::msg::TransformStamped transformStamped; 
  geometry_msgs::msg::PoseStamped message, actual;
  
  std::unique_ptr<tf2_ros::Buffer> buffer = std::make_unique<tf2_ros::Buffer>(node->get_clock());
  std::shared_ptr<tf2_ros::TransformListener> listener = std::make_shared<tf2_ros::TransformListener>(*buffer);	// No lo dejo como listener(buffer) porque cambio el std::make_unique y make_shared

  rclcpp::WallRate loop_rate(500ms);
    
  double x[3]={2.8, -3.21, -9.5}, y[3]={-6.1, -4.1, -4.5}, difx, dify;
  int contador = 0;	// Contador para saber por cual posición voy
  
  while (rclcpp::ok() && contador <= 3) {
    message.pose.position.x = x[contador];
    message.pose.position.y = y[contador];
    
    publisher->publish(message);
    
    transformStamped = buffer->lookupTransform("base_footprint", "map", rclcpp::Time(0), rclcpp::Duration(5s));   
    tf2::doTransform(message, actual, transformStamped);
    
    difx = std::abs(actual.pose.position.x); 
    dify = std::abs(actual.pose.position.y); 
    
    if ((difx < 0.3) && (dify < 0.3))
    	contador++;    
    
    rclcpp::spin_some(node);
    loop_rate.sleep();

  }
  rclcpp::shutdown();
  return 0;
}

