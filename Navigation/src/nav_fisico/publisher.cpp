#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/pose_with_covariance_stamped.hpp"
#include <iostream>
#include <cstdlib>

using namespace std::chrono_literals;

double AMCLx, AMCLy;
void topic_callback(const geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg)
{
   AMCLx = msg->pose.pose.position.x;
   AMCLy = msg->pose.pose.position.y;
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("publisher");
  auto publisher = node->create_publisher<geometry_msgs::msg::PoseStamped>("goal_pose", 10);
  auto subscription = node->create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>("amcl_pose", 10, topic_callback);
  geometry_msgs::msg::PoseStamped message;
  
  rclcpp::WallRate loop_rate(500ms);
    
  double x[3]={2.8, -3.21, -9.5}, y[3]={-6.1, -4.1, -4.5}, difx, dify;
  int contador = 0;	// Contador para saber por cual posición voy
  
  while (rclcpp::ok() && contador <= 3) {
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

