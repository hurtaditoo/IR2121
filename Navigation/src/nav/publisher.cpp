#include <chrono>
#include <iostream>
#include <cstdlib>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "tf2_ros/transform_listener.h"
#include "geometry_msgs/transform_stamped.hpp"

using namespace std::chrono_literals;

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("publisher");
  auto publisher = node->create_publisher<geometry_msgs::msg::PoseStamped>("goal_pose", 10);
    
  geometry_msgs::TransformStamped transformStamped; 
  geometry_msgs::msg::PoseStamped message;
  
  std::unique_ptr<tf2_ros::Buffer> buffer = std::make_unique<tf2_ros::Buffer>(this->get_clock());
  std::shared_ptr<tf2_ros::TransformListener> listener = std::make_shared<tf2_ros::TransformListener>(*buffer);	// No lo dejo como listener(buffer) porque cambio el std::make_unique y make_shared

  rclcpp::WallRate loop_rate(500ms);
    
  double x[4]={-1, 4, 8.08, 2.9}, y[4]={3, 4.85, 0.12, 0.91}, difx, dify;
  int contador = 0;	// Contador para saber por cual posición voy
  
  while (rclcpp::ok() && contador <= 4) {
    message.pose.position.x = x[contador];
    message.pose.position.y = y[contador];
    
    publisher->publish(message);
    
    difx = std::abs(message.pose.position.x); 
    dify = std::abs(message.pose.position.y); 
    
    transformStamped = buffer->lookupTransform("base_footprint", "map", rrclp::Time(0), rrclp::Duration(5s);   
    tf2::doTransform(message, transformStamped);
    
    if ((difx < 0.3) && (dify < 0.3))
    	contador++;    
    
    rclcpp::spin_some(node);
    loop_rate.sleep();

  }
  rclcpp::shutdown();
  return 0;
}

