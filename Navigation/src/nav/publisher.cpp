#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "tf2_ros/transform_listener.h"
#include "geometry_msgs/transform_stamped.hpp"
#include <iostream>
#include <cstdlib>

using namespace std::chrono_literals;

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("publisher");
  auto publisher = node->create_publisher<geometry_msgs::msg::PoseStamped>("goal_pose", 10);
    
  geometry_msgs::TransformStamped transformStamped; 
  geometry_msgs::msg::PoseStamped message;
  
  <tf2_ros/Buffer> tf2_ros::Buffer buffer;
  <tf2_ros/TransformListener> tf2_ros::TransformListener listener(buffer);

  rclcpp::WallRate loop_rate(500ms);
    
  double x[4]={-1, 4, 8.08, 2.9}, y[4]={3, 4.85, 0.12, 0.91}, difx, dify;
  int contador = 0;	// Contador para saber por cual posición voy
  
  while (rclcpp::ok() && contador <= 4) {
    message.pose.position.x = x[contador];
    message.pose.position.y = y[contador];
    
    publisher->publish(message);
    
    difx = std::abs(message.pose.position.x); 
    dify = std::abs(message.pose.position.y); 
    
    if ((difx < 0.3) && (dify < 0.3))
    	contador++;    
    	
    transformStamped = buffer.lookupTransform("base_link", "map" rrclp::Time(0), rrclp::Duration(5.0);
    
    tf2::doTransform(message, transformStamped);
    
    rclcpp::spin_some(node);
    loop_rate.sleep();

  }
  rclcpp::shutdown();
  return 0;
}

