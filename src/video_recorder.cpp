#include "video_recorder.h"
#include <rosbag/bag.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <boost/filesystem.hpp>



video_recorder::video_recorder(ros::NodeHandle nh)
{
    nh_ = nh;
}

void video_recorder::start_recording()
{
    if(bag_.isOpen()){
        ROS_INFO("Bag already open/recording.")
        return
    }
    std::string video_name = create_file();
    bag_.open(video_name, rosbag::bagmode::Write);
    cam_sub_ = nh_.subscribe("/camera/rgb/image_raw",1,&video_recorder::cameraCallback, this);
    ROS_INFO("Recording starting into file %s",video_name);
}

void video_recorder::stop_recording()
{
    cam_sub_.shutdown();
    bag_.close();
    ROS_INFO("Recording Stoped");
}

void video_recorder::cameraCallback(const sensor_msgs::Image::ConstPtr &msg)
{
    bag_.write("/camera/rgb/image_raw",ros::Time::now(),msg);
}

std::string video_recorder::create_file()
{   
    std::string file_path;
    if(nh_.getParam("video_file_path",file_path)){
        boost::filesystem::path dir ("file_path");
        boost::filesystem::path file ("video_" + datetime() + ".bag");
        boost::filesystem::path full_path = dir / file;
        return full_path.c_str();
    }
    return std::string();
}

std::string datetime()
{
    time_t raw_time;
    struct tm * time_info;
    char buffer[80];

    time (&raw_time);
    time_info = localtime(&raw_time);

    strftime(buffer,80,"%Y-%m-%d %H-%M-%S",time_info);
    return std::string(buffer);
}