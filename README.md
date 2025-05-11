# IR2121 - Mobile Robotics

This repository features a variety of simulation-based and real-world robotics experiments completed during the **IR2121 - Mobile Robotics** course, part of the 3rd year in the **Robotic Intelligence Bachelor's Degree** at **Universitat Jaume I**.

Throughout the course, we explored key principles of autonomous mobile robot navigation, including real-time localization, mapping, sensor fusion, and configuration of the navigation stack using **ROS2**, **Webots**, and **RViz2**.

---

## 📂 Overview of Projects

### 📦 Data Logging & Playback
- Remote control of a **TurtleBot3** in:
  - A real-life environment inside the faculty
  - A simulated household using **Webots**
- Collected sensor data with `rosbag2` and analyzed it using **rqt** and **RViz2**

### 📌 Robot Localization with Nav2
- Applied the **Nav2** framework to localize the robot within existing maps
- Worked with **AMCL** to tune localization behavior and manage **costmaps**
- Tracked robot positions and orientations using **RViz2**

### 🚧 Mapping via SLAM
- Created 2D maps in both simulated and physical environments:
  - Virtual mapping in Webots
  - Real mapping inside the university building
- Implemented SLAM techniques and integrated them into the robot’s navigation workflow

### 🧭 Final Navigation Task
- Developed a goal-based navigation system using:
  - **Nav2 Action Server** to send targets
  - Status feedback to monitor and interrupt navigation when needed
  - **TF2** library to manage coordinate frames and robot tracking

---

## 🛠️ Tools and Frameworks

- **ROS2** (Foxy / Humble versions)
- **Webots Simulator**
- **RViz2 Visualization Tool**
- **rqt GUI Tools** & **rosbag2**
- **Navigation2 (Nav2)**
- **TF2 Transform Management**

---

## 🎓 Key Takeaways

- Built and tested autonomous navigation in 2D environments
- Combined SLAM and localization techniques in both simulation and real-world scenarios
- Gained hands-on skills in teleoperation, environmental mapping, and goal-oriented movement
- Developed a strong command of the **ROS2 ecosystem**, from basic topic handling to advanced navigation stacks
