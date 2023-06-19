
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
 *    https://temoto-telerobotics.github.io
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <class_loader/class_loader.hpp>
#include "ta_component_pipe_test/temoto_action.h"
#include "temoto_component_manager/component_manager_interface.h"
#include "std_msgs/String.h"

/* 
 * ACTION IMPLEMENTATION of TaComponentPipeTest 
 */
class TaComponentPipeTest : public TemotoAction
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
  cmi_.initialize();
  temoto_core::TopicContainer test_a_responded_topics = cmi_.startPipe("tests");
  std::string test_2a_topic_t4 = test_a_responded_topics.getOutputTopic("data_type_4");
  std::string test_2a_topic_t5 = test_a_responded_topics.getOutputTopic("data_type_5");
  TEMOTO_INFO_STREAM("(test_2a) Got data_4 on topic '" << test_2a_topic_t4 << "'");
  TEMOTO_INFO_STREAM("(test_2a) Got data_5 on topic '" << test_2a_topic_t5 << "'");

  ros::Subscriber test_2a_subscriber_1 = n_.subscribe(test_2a_topic_t4, 10, &TaComponentPipeTest::test2ACallback1, this);
  ros::Subscriber test_2a_subscriber_2 = n_.subscribe(test_2a_topic_t5, 10, &TaComponentPipeTest::test2ACallback2, this);

  ros::Duration(20).sleep();
}

void test2ACallback1(const std_msgs::String& msg)
{
  TEMOTO_INFO_STREAM_(msg.data);
}

void test2ACallback2(const std_msgs::String& msg)
{
  TEMOTO_INFO_STREAM_(msg.data);
}

// Destructor
~TaComponentPipeTest()
{
  TEMOTO_INFO("Action instance destructed");
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Class members
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
// Nodehandle
ros::NodeHandle n_;

// Create sensor manager interface object for accessing sensor manager
temoto_component_manager::ComponentManagerInterface cmi_;

}; // TaComponentPipeTest class

/* REQUIRED BY CLASS LOADER */
CLASS_LOADER_REGISTER_CLASS(TaComponentPipeTest, ActionBase);
