#!/bin/bash
source /opt/ros/foxy/setup.bash
ros2 run tf2_ros static_transform_publisher 12.2 -30 0 0 0 0.1305262 0.991449 map odom
