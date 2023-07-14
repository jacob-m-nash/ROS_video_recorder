#include <video_recorder.h>

int main(int argc, char **argv){
  
  ros::init(argc,argv, "video_recorder node");
  ros::NodeHandle nh;

  // create an instance of the class
  video_recorder video_recorder(nh);

  // User imput to start recording
  bool start_recording = false;
  std:: string input_string;
    while(!start_recording){
        ROS_INFO("Enter 'start' to start recording");
        std::getline(std::cin, input_string);
        if(input_string == "start"){
            start_recording = true;
        }
        else{
            ROS_INFO("Wrong input... try again");
        }
    }
  video_recorder.start_recording();
  //TODO Maybe button to stop recording (unsubscribe and close bag)

  // loop rate in Hz
  ros::Rate rate(60);

  while (ros::ok()) {

    // spin and process all pending callbacks
    ros::spinOnce();

    // sleep to fulfill the loop rate
    rate.sleep();
  }
}
