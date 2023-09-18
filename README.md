# Unitree IMU

Extracts IMU data from Unitree HighState message and publishes the data as an IMU sensor message.

# Dependency
- unitree_legged_msgs

# Install
- Download the repository into your workspace src folder
- catkin_make

# Use
```
roslaunch unitree_imu unitree_imu.launch
```

# unitree_imu_node
### Published topic:
- sensor_msg::IMU

### Subscribed topic:
- unitree_legged_msg::HighState
