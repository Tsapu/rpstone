#include "ros/ros.h"

#include <rpstone/Gesture.h>
#include "std_msgs/String.h"

#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace::std;

vector<string> winnerVector;
ros::Publisher pub; 
std_msgs::String win_player;

void gestureCallback(const rpstone::Gesture::ConstPtr& msg)
{   
    string winner;

    if ((msg->player1_gesture == "") && (msg->player2_gesture != ""))
    {
        winner = "player2";
    }
    else if (msg->player1_gesture == "rock")
    {
        if (msg->player2_gesture == "paper")
        {
            winner = "player2";
        }
        else if (msg->player2_gesture == "scissors")
        {
            winner = "player1";
        }
    }
    else if (msg->player1_gesture == "paper")
    {
        if (msg->player2_gesture == "scissors")
        {
            winner = "player2";
        }
        else if (msg->player2_gesture == "rock")
        {
            winner = "player1";
        }
    }
    else if (msg->player1_gesture == "scissors")
    {
        if (msg->player2_gesture == "rock")
        {
            winner = "player2";
        }
        else if (msg->player2_gesture == "paper")
        {
            winner = "player1";
        }
    }
    else if ((msg->player2_gesture == "") && (msg->player1_gesture != ""))
    {
        winner = "player1";
    }    
    
    if (winner == "player1" || winner == "player2")
    {
        // cout << "Player1: " << msg->player1_gesture.c_str() << endl;
        // cout << "Player2: " << msg->player2_gesture.c_str() << endl;
        // cout << "Winner: " << winner << endl;
        // cout << "---------------------------" << endl;
        
        
        // win_player.data = winner;
        // pub.publish(win_player);

        winnerVector.push_back(winner);
        

        if (winnerVector.size() == 11)
        {   
            int count_player1 = 0;
            int count_player2 = 0;
            
            for (int i=0; i<winnerVector.size(); i++)
            {
                if (winnerVector[i] == "player1")
                {
                    count_player1++;
                }
                else
                {
                    count_player2++;
                }
            }

            if (count_player1 > count_player2)
            {
                win_player.data = "player1";
            }
            else
            {
                win_player.data = "player2";
            }

            ROS_INFO("Winner: %s \n", win_player.data.c_str());
            pub.publish(win_player);
            winnerVector.clear();
        }
    }
    
    

    // ROS_INFO("%s", winner);
    // winnerVector.push_back(winner);
    // std_msgs::String win_player;

    // if (sizeof(winnerVector)/sizeof(winnerVector[0]) == 11)
    // {
    //     int count_player1 = 0;
    //     int count_player_2 = 0;
    //     for (const auto& player: winnerVector)
    //     {
    //         if (player == "player1")
    //         {
    //             count_player1++;
    //         }
    //         else
    //         {
    //             count_player_2++;
    //         }
    //     }

        
    //     if (count_player1 > count_player_2)
    //     {
    //         win_player.data = "player1";
    //     }
    //     else
    //     {
    //         win_player.data = "player2";
    //     }

          
    // }
    // win_player.data = winner;
    // pub.publish(win_player);
    // ROS_INFO("Winner: %s", win_player.data.c_str());
    // winnerVector.clear();

    // ROS_INFO("Player1: %s", msg->player1_gesture.c_str());
    // ROS_INFO("Player2: %s", msg->player2_gesture.c_str());

    
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "winner");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe<rpstone::Gesture>("/rps_gestures", 10, gestureCallback);
  pub = nh.advertise<std_msgs::String>("/winning_player", 10);

  ros::spin();

  return 0;
}