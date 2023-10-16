#!/bin/bash
source /opt/ros/foxy/setup.bash
ros2 run tf2_ros static_transform_publisher -5.2 3 0 0 0 0.1564345 0.9876883 map odom
