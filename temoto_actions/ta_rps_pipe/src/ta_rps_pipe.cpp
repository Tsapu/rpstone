
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *
 *  The basis of this file has been automatically generated
 *  by the TeMoto action package generator. Modify this file
 *  as you wish but please note:
 *
 *    WE HIGHLIY RECOMMEND TO REFER TO THE TeMoto ACTION
 *    IMPLEMENTATION TUTORIAL IF YOU ARE UNFAMILIAR WITH
 *    THE PROCESS OF CREATING CUSTOM TeMoto ACTION PACKAGES
 *    
 *  because there are plenty of components that should not be
 *  modified or which do not make sence at the first glance.
 *
 *  See TeMoto documentation & tutorials at: 
 *    https://github.com/temoto-framework
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <vector>
#include <class_loader/class_loader.hpp>
#include "ta_rps_pipe/temoto_action.h"
#include <temoto_component_manager/component_manager_interface.h>
#include "rpstone/Gesture.h"
#include <std_msgs/String.h>
// #include <ros_openpose/Frame.h>

using namespace std;

/* 
 * ACTION IMPLEMENTATION of TaRpsPipe 
 */
class TaRpsPipe : public TemotoAction
{
public:

/*
 * Function that gets invoked only once (when the action is initialized) throughout the action's lifecycle
 */
void initializeTemotoAction()
{
  /* * * * * * * * * * * * * * * * * * * * * * *
   *                          
   * ===> YOUR INITIALIZATION ROUTINES HERE <===
   *                          
   * * * * * * * * * * * * * * * * * * * * * * */

  TEMOTO_INFO_STREAM("Action initialized");
}

/*
 * Function that gets invoked when the action is executed (REQUIRED)
 */
void executeTemotoAction()
try
{
  // getInputParameters();
  
  cmi_.initialize();
  temoto_core::TopicContainer test_a_responded_topics = cmi_.startPipe("rps_game");
  // rpstone::Gesture test_2a_topic_t4 = test_a_responded_topics.getOutputTopic("gestures");
  std::string test_2a_topic_t5 = test_a_responded_topics.getOutputTopic("gestures");
  // TEMOTO_INFO_STREAM("(test_2a) Got RPS on topic '" << test_2a_topic_t5->player2_gesture.c_str() << "'");
  TEMOTO_INFO_STREAM("(test_2a) Got RPS on topic '" << test_2a_topic_t5 << "'");

  // ros::Subscriber test_2a_subscriber_1 = n_.subscribe(test_2a_topic_t4, 10, &TaComponentPipeTest::test2ACallback1, this);
  ros::Subscriber test_2a_subscriber_2 = n_.subscribe(test_2a_topic_t5, 10, &TaRpsPipe::test2ACallback1, this);
  // ros::Publisher pub_ = n_.advertise<std_msgs::String>("/winning_player", 10);

  while (actionOk())
  {
    ros::Duration(0.5).sleep();
  }

  // setOutputParameters();
}
catch(temoto_core::error::ErrorStack& error_stack)
{
  std::cout << error_stack << std::endl;
}

void test2ACallback1(const rpstone::Gesture::ConstPtr& msg)
{
  // TEMOTO_INFO_STREAM_(msg.data);
  std::string winner;
  
  std::string player1Gesture = msg->player1_gesture;
  std::string player2Gesture = msg->player2_gesture;
  
  // TEMOTO_INFO_STREAM("Player 1 Gesture: " << player1Gesture.c_str());
  // TEMOTO_INFO_STREAM("Player 2 Gesture: " << player2Gesture.c_str());

  if (player1Gesture == "" && player2Gesture != "")
  {

  }

  else if (player1Gesture == "rock")
  {
    if (player2Gesture == "paper")
    {
      winner = "player2";
    }
    else if (player2Gesture == "scissors")
    {
      winner = "player1";
    }
  }

  else if (player1Gesture == "paper")
  {
    if (player2Gesture == "scissors")
    {
      winner = "player2";
    }
    else if (player2Gesture == "rock")
    {
      winner = "player1";
    }
  }

  else if (player1Gesture == "scissors")
  {
    if (player2Gesture == "rock")
    {
      winner = "player2";
    }  
    else if (player2Gesture == "paper")
    {
      winner = "player1";
    }
  }

  else if (player2Gesture == "" && player1Gesture != "")
  {
    winner = "palyer1";
  }

  if (winner == "player1" || winner == "player2")
  {
    winnerVector.push_back(winner);

    if (winnerVector.size() == 11)
    {
      int count_player1 = 0;
      int count_player2 = 0;

      for (int i = 0; i < winnerVector.size(); i++)
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
      pub_.publish(win_player);
      winnerVector.clear();

    }

  }

}

// Destructor
~TaRpsPipe()
{
  TEMOTO_INFO("Action instance destructed");
}

// Loads in the input parameters
void getInputParameters()
{
  // no input params for this action
}

// Sets the output parameters which can be passed to other actions
void setOutputParameters()
{
  // no output params for this action
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Class members
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
// Nodehandle
ros::NodeHandle n_;
ros::Publisher pub_ = n_.advertise<std_msgs::String>("/winning_player", 10);

vector<string> winnerVector;
std_msgs::String win_player;

// Create sensor manager interface object for accessing sensor manager
temoto_component_manager::ComponentManagerInterface cmi_;

}; // TaRpsPipe class

/* REQUIRED BY CLASS LOADER */
CLASS_LOADER_REGISTER_CLASS(TaRpsPipe, ActionBase);
