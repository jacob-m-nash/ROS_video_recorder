#ifndef VIDEO_RECORDER_H
#define VIDEO_RECORDER_H

#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#include <rosbag/bag.h>

class video_recorder
{
private:
    bool start_recording_ = false;
    rosbag::Bag bag_;
    ros::NodeHandle nh_;
    ros::Subscriber cam_sub_;
    void cameraCallback(const sensor_msgs::Image::ConstPtr &msg);
    std::string create_file();

public:
    video_recorder(ros::NodeHandle nh);
    
    void start_recording();
    void stop_recording();
   
};

std::string datetime();





#endif