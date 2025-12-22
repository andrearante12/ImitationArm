# Robotic Arm

## Visualization with rviz2

https://docs.ros.org/en/jazzy/p/rviz2/

### Steps to run

1. Create a ROS package
```
cd ~/ros2_ws/src
ros2 pkg create --build-type ament_cmake --license Apache-2.0 robotic_arm
```

2. Add the contents of the robotic_arm folder into the package directory `~/ros2_ws/src/robotic_arm`. Replace `./robotic_arm` to the location of this cloned repo.
```
cp -rf ./robotic_arm ~/ros2_ws/src/robotic_arm
```

3. Build the package (Full Rebuild)
```
cd ~/ros2_ws
rm -rf build install log
colcon build
source /opt/ros/jazzy/setup.bash
source install/setup.bash
```

Alternatively, a quick rebuild alternative for minor changes to code
```
cd ~/ros2_ws
colcon build --packages-select robotic_arm
source install/setup.bash
```

4. Run the visualization with
```
ros2 launch robotic_arm robotic_arm.launch.py

```
