#include <ros/ros.h>
#include <rpstone/Gesture.h>

//function that confirms a guesture from node if the are 10 consecutive frames with the same gesture

void gestureCallback(const std_msgs::String::ConstPtr& msg) {
    ROS_INFO("I heard: [%s]", msg->data.c_str());
    std::string gesture = msg->data.c_str();
    static int count = 0;  // Declare count as static to retain its value between callbacks
    if (gesture != msg->data.c_str()) {
        count = 1;  // Reset the count if the gesture has changed
    } else if (count >= 10) {
        ROS_INFO("Gesture confirmed: [%s]", msg->data.c_str());
        count = 0;  // Reset the count after confirming the gesture
        judgeRPS(msg);
    } else {
        count++;
    }
}


//rock appper scissors judge

void judgeRPS(const std_msgs::String::ConstPtr& msg) {
    const char* gesture = msg->data.c_str();
    if (strcmp(gesture, "rock") == 0) {
        if (strcmp(gesture, "paper") == 0) {
            ROS_INFO("You lose");
        } else if (strcmp(gesture, "scissors") == 0) {
            ROS_INFO("You win");
        } else {
            ROS_INFO("Draw");
        }
    } else if (strcmp(gesture, "paper") == 0) {
        if (strcmp(gesture, "scissors") == 0) {
            ROS_INFO("You lose");
        } else if (strcmp(gesture, "rock") == 0) {
            ROS_INFO("You win");
        } else {
            ROS_INFO("Draw");
        }
    } else if (strcmp(gesture, "scissors") == 0) {
        if (strcmp(gesture, "rock") == 0) {
            ROS_INFO("You lose");
        } else if (strcmp(gesture, "paper") == 0) {
            ROS_INFO("You win");
        } else {
            ROS_INFO("Draw");
        }
    }
}


int main(int argc, char** argv) {
    ros::init(argc, argv, "gesture_confirmation_node");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/rps_gestures", 1, gestureCallback);
    ros::spin();
    return 0;
}