#include "ros/ros.h"
#include <ros_openpose/Frame.h>
#include <ros_openpose/Person.h>
#include <ros_openpose/BodyPart.h>
#include <ros_openpose/Pixel.h>

// #include <geometry_msgs/Point32.h>

void openposeCallback(const ros_openpose::Frame::ConstPtr& msg)
{
    // Iterate through each person detected
    for (const ros_openpose::Person& person : msg->persons)
    {
        // Iterate through each left hand body part of the person
        for (const ros_openpose::BodyPart& leftHandPart : person.leftHandParts)
        {
			 // Access the pixel field
            ros_openpose::Pixel pixel = leftHandPart.pixel;
            float pixelX = pixel.x;
            float pixelY = pixel.y;
            
			// Print the extracted pixel coordinates
            ROS_INFO("Left Hand Pixel: x=%.2f, y=%.2f", pixelX, pixelY);
        }
    }
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "hand_detector");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe<ros_openpose::Frame>("/frame", 10, openposeCallback);

  ros::spin();

  return 0;
}



