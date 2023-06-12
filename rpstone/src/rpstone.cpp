#include <ros/ros.h>
#include <rpstone/Gesture.h>

// Function to judge the rock-paper-scissors game
void judgeRPS(const rpstone::Gesture::ConstPtr& msg);

// Function that confirms a gesture from player 1 and player 2
void gestureCallback(const rpstone::Gesture::ConstPtr& msg) {
    // ROS_INFO("player1_gesture: [%s]", msg->player1_gesture.c_str());
    // ROS_INFO("player2_gesture: [%s]", msg->player2_gesture.c_str());

    static int count = 0;  // Declare count as static to retain its value between callbacks
    static std::string previousPlayer1Gesture = "";
    static std::string previousPlayer2Gesture = "";

    if (msg->player1_gesture != previousPlayer1Gesture || msg->player2_gesture != previousPlayer2Gesture) {
        count = 1;  // Reset the count if either player's gesture has changed
    } else if (count >= 10) {
        ROS_INFO("Gesture confirmed - Player 1: [%s], Player 2: [%s]", msg->player1_gesture.c_str(), msg->player2_gesture.c_str());
        count = 0;  // Reset the count after confirming the gesture
        judgeRPS(msg);  // Call judgeRPS function
    } else {
        count++;
    }

    previousPlayer1Gesture = msg->player1_gesture;
    previousPlayer2Gesture = msg->player2_gesture;
}

// Function to judge the rock-paper-scissors game
void judgeRPS(const rpstone::Gesture::ConstPtr& msg) {
    std::string player1Gesture = msg->player1_gesture;
    std::string player2Gesture = msg->player2_gesture;

    if (player1Gesture == "rock") {
        if (player2Gesture == "paper") {
            ROS_INFO("Player 2 wins!");
        } else if (player2Gesture == "scissors") {
            ROS_INFO("Player 1 wins!");
        } else {
            ROS_INFO("It's a draw!");
        }
    } else if (player1Gesture == "paper") {
        if (player2Gesture == "scissors") {
            ROS_INFO("Player 2 wins!");
        } else if (player2Gesture == "rock") {
            ROS_INFO("Player 1 wins!");
        } else {
            ROS_INFO("It's a draw!");
        }
    } else if (player1Gesture == "scissors") {
        if (player2Gesture == "rock") {
            ROS_INFO("Player 2 wins!");
        } else if (player2Gesture == "paper") {
            ROS_INFO("Player 1 wins!");
        } else {
            ROS_INFO("It's a draw!");
        }
    } else {
        ROS_INFO("Invalid gestures!");
    }
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "gesture_confirmation_node");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/rps_gestures", 1, gestureCallback);
    ros::spin();
    return 0;
}
