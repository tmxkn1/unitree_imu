/*
 * Extracts the IMU data from the unitree_legged_msg/HighState and publishes it as a sensor_msgs/Imu
 */

#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <unitree_legged_msgs/HighState.h>

static ros::Publisher pub;
static std::string frame_id;

void callback(const unitree_legged_msgs::HighState &state)
{
    sensor_msgs::Imu imu;
    imu.header.frame_id = frame_id;
    imu.orientation.x = state.imu.quaternion[0];
    imu.orientation.y = state.imu.quaternion[1];
    imu.orientation.z = state.imu.quaternion[2];
    imu.orientation.w = state.imu.quaternion[3];
    imu.angular_velocity.x = state.imu.rpy[0];
    imu.angular_velocity.y = state.imu.rpy[1];
    imu.angular_velocity.z = state.imu.rpy[2];
    imu.linear_acceleration.x = state.imu.accelerometer[0];
    imu.linear_acceleration.y = state.imu.accelerometer[1];
    imu.linear_acceleration.z = state.imu.accelerometer[2];

    // Unitree does not publish covariance data
    imu.orientation_covariance.fill(0);
    imu.angular_velocity_covariance.fill(0);
    imu.linear_acceleration_covariance.fill(0);

    pub.publish(imu);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "unitree_imu");
    ros::NodeHandle node;
    ros::NodeHandle priv("~");

    priv.param<std::string>("frame_id", frame_id, "unitree");

    pub = node.advertise<sensor_msgs::Imu>("imu", 10);
    ros::Subscriber fix_sub = node.subscribe("high_state", 10, callback);

    ros::spin();
}
