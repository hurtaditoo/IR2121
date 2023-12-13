#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "tf2_ros/transform_listener.h"
#include "geometry_msgs/TransformStamped.h"
#include <iostream>
#include <cstdlib>

using namespace std::chrono_literals;

double AMCLx, AMCLy;

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("publisher");
  auto publisher = node->create_publisher<geometry_msgs::msg::PoseStamped>("goal_pose", 10);
  
  tf2_ros::Buffer tfBuffer;
  tf2_ros::TransformListener tfListener(tfBuffer);
  
  geometry_msgs::msg::PoseStamped message;
  
  rclcpp::WallRate loop_rate(500ms);
    
  double x[4]={-1, 4, 8.08, 2.9}, y[4]={3, 4.85, 0.12, 0.91}, difx, dify;
  int contador = 0;	// Contador para saber por cual posición voy
  
  while (rclcpp::ok() && contador <= 4) {
    message.pose.position.x = x[contador];
    message.pose.position.y = y[contador];
    
    publisher->publish(message);
    
    difx = std::abs(x[contador] - AMCLx); 
    dify = std::abs(y[contador] - AMCLy); 
    
    if ((difx < 0.3) && (dify < 0.3))
    	contador++;
    
    rclcpp::spin_some(node);
    loop_rate.sleep();

  }
  rclcpp::shutdown();
  return 0;
}

