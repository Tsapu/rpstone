#include "ros/ros.h"

#include <rpstone/Gesture.h>

// #include <geometry_msgs/Point32.h>

void gestureCallback(const rpstone::Gesture::ConstPtr& msg)
{   
    
    return;
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "hand_detector");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe<rpstone::Gesture>("/rps_gestures", 10, gestureCallback);

  ros::spin();

  return 0;
}



