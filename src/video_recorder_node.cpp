#include <video_recorder.h>

// #include <stdio.h> maybe dont need
#include <unistd.h> // maybe dont need
#include <termios.h>

char key(' ');

// For non-blocking keyboard inputs
int getch(void)
{
  int ch;
  struct termios oldt;
  struct termios newt;

  // Store old settings, and copy to new settings
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;

  // Make required changes and apply the settings
  newt.c_lflag &= ~(ICANON | ECHO);
  newt.c_iflag |= IGNBRK;
  newt.c_iflag &= ~(INLCR | ICRNL | IXON | IXOFF);
  newt.c_lflag &= ~(ICANON | ECHO | ECHOK | ECHOE | ECHONL | ISIG | IEXTEN);
  newt.c_cc[VMIN] = 1;
  newt.c_cc[VTIME] = 0;
  tcsetattr(fileno(stdin), TCSANOW, &newt);

  // Get the current character
  ch = getchar();

  // Reapply old settings
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  return ch;
}

int main(int argc, char **argv){
  
  ros::init(argc,argv, "video_recorder node");
  ros::NodeHandle nh;

  // create an instance of the class
  video_recorder video_recorder(nh);

  // loop rate in Hz
  ros::Rate rate(60);

  ROS_INFO("Recorder controls: Start Recording 's'  Stop Recording 'd'  Close: 'CTRL-C'");

  while (ros::ok()) {

    key = getch();

    if(key == 's'){
      video_recorder.start_recording();
    }
    else if (key == 'd')
    {
      video_recorder.stop_recording();
    }
    

    // spin and process all pending callbacks
    ros::spinOnce();

    // sleep to fulfill the loop rate
    rate.sleep();
  }
}
