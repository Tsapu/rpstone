
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

#include <class_loader/class_loader.hpp>
#include "ta_rps_pipe/temoto_action.h"
#include <temoto_component_manager/component_manager_interface.h>
#include "rpstone/Gesture.h"
// #include <ros_openpose/Frame.h>

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

  ros::Duration(10).sleep();

  // setOutputParameters();
}

void test2ACallback1(const rpstone::Gesture::ConstPtr& msg)
{
  // TEMOTO_INFO_STREAM_(msg.data);
  std::string player2Gesture = msg->player2_gesture;
  TEMOTO_INFO_STREAM("Player 2 Gesture: " << player2Gesture.c_str());
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

// Create sensor manager interface object for accessing sensor manager
temoto_component_manager::ComponentManagerInterface cmi_;

}; // TaRpsPipe class

/* REQUIRED BY CLASS LOADER */
CLASS_LOADER_REGISTER_CLASS(TaRpsPipe, ActionBase);
