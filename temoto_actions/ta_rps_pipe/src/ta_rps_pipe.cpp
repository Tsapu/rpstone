
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
#include "temoto_process_manager/process_manager_interface.hpp"
#include <ros/package.h>
#include <map>
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
  //pmi_(true);
  temoto_process_manager::ProcessManagerInterface pmi_(true);
  cmi_.initialize();

  temoto_core::TopicContainer rps_responded_topics = cmi_.startPipe("rps_game");
  // rpstone::Gesture test_2a_topic_t4 = test_a_responded_topics.getOutputTopic("gestures");
  std::string gesture_topic = rps_responded_topics.getOutputTopic("gestures");
  // TEMOTO_INFO_STREAM("(test_2a) Got RPS on topic '" << test_2a_topic_t5->player2_gesture.c_str() << "'");
  TEMOTO_INFO_STREAM("[ta_rps_pipe] Got RPS on topic '" << gesture_topic << "'");

  ros::Subscriber gesture_sub = n_.subscribe(gesture_topic, 10, &TaRpsPipe::gesture_cb, this);

  // load twist node:
  pmi_.loadRosResource("rpstone", "rptwist");
  // ros::Duration(2).sleep();
  // temoto_process_manager::LoadProcess load_sound_msg = pmi_.loadSysResource("play", sound_path + "countdown.mp3");

  while (actionOk())
  {
    // play countdown:
    // game_time 
    if (WINNER_FOUND) {
      TEMOTO_INFO_STREAM("WINNER FOUND, NEW ROUND!");
      if (player_nr == 1) {
        TEMOTO_INFO_STREAM("WINNER == 1");
        temoto_process_manager::LoadProcess load_win_sound_1 = pmi_.loadSysResource("play", sound_path + "p1_wins.mp3");
        ros::Duration(2.5).sleep();
        pmi_.unloadResource(load_win_sound_1);
      } else if (player_nr == 2) {
        TEMOTO_INFO_STREAM("WINNER == 2");
        temoto_process_manager::LoadProcess load_win_sound_2 = pmi_.loadSysResource("play", sound_path + "p2_wins.mp3");
        ros::Duration(2.5).sleep();
        pmi_.unloadResource(load_win_sound_2);
      } else if (player_nr == 3) {
        TEMOTO_INFO_STREAM("DRAW");
        temoto_process_manager::LoadProcess load_draw = pmi_.loadSysResource("play", sound_path + "trumpet.wav");
        ros::Duration(1).sleep();
        pmi_.unloadResource(load_draw);
      }
      WINNER_FOUND = false;
      player_nr = 999;
      GAME_ACTIVE = false;
      temoto_process_manager::LoadProcess load_sound_msg = pmi_.loadSysResource("play", sound_path + "countdown.mp3");
      ros::Duration(2.8).sleep();
      pmi_.unloadResource(load_sound_msg);
      GAME_ACTIVE = true;
    }
    // sleep
    ros::Duration(0.02).sleep();
  }

  // setOutputParameters();
}
catch(temoto_core::error::ErrorStack& error_stack)
{
  std::cout << error_stack << std::endl;
}

void gesture_cb(const rpstone::Gesture::ConstPtr& msg)
{
  // TEMOTO_INFO_STREAM_(msg.data);
  std::string winner;
  
  std::string player1Gesture = msg->player1_gesture;
  std::string player2Gesture = msg->player2_gesture;
  
  // TEMOTO_INFO_STREAM("Player 1 Gesture: " << player1Gesture.c_str());
  // TEMOTO_INFO_STREAM("Player 2 Gesture: " << player2Gesture.c_str());
  if (!GAME_ACTIVE) {
    return;
  }

  if (player1Gesture == "" && player2Gesture != "")
  {

  }

  else if (player1Gesture == player2Gesture && player1Gesture != "")
  {
    winner = "draw";
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
    winner = "player1";
  }

  if (winner == "player1" || winner == "player2" || winner == "draw")
  {
    winnerVector.push_back(winner);

    if (winnerVector.size() == 5)
    {
      int count_player1 = 0;
      int count_player2 = 0;
      int draw_count = 0;

      for (int i = 0; i < winnerVector.size(); i++)
      {
        if (winnerVector[i] == "player1")
        {
          count_player1++;
        } else if (winnerVector[i] == "draw") {
          draw_count++;
        }
        else
        {
          count_player2++;
        }
      }

      if (draw_count >= 4) { 
        WINNER_FOUND = true;
        player_nr = 3;
        win_player.data = "draw";
      }

      else if (count_player1 > count_player2)
      {
        win_player.data = "player1";
        WINNER_FOUND = true;
        player_nr = 1;
      }
      else
      {
        win_player.data = "player2";
        WINNER_FOUND = true;
        player_nr = 2;
      }

      TEMOTO_INFO_STREAM("Winner: " << win_player.data.c_str());
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
ros::Publisher pub_ = n_.advertise<std_msgs::String>("winning_player", 10);

vector<string> winnerVector;
std_msgs::String win_player;
std::string sound_path = ros::package::getPath("rpstone") + "/sounds/";
// temoto_process_manager::LoadProcess load_sound_msg;
temoto_process_manager::LoadProcess load_win_sound;

bool GAME_ACTIVE = false;
bool WINNER_FOUND = true;
int player_nr = 999;

// Initialize process manager interface
// temoto_process_manager::ProcessManagerInterface pmi_;
// Create the component manager interface
temoto_component_manager::ComponentManagerInterface cmi_;

}; // TaRpsPipe class

/* REQUIRED BY CLASS LOADER */
CLASS_LOADER_REGISTER_CLASS(TaRpsPipe, ActionBase);