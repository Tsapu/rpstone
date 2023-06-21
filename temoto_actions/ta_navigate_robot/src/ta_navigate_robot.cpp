
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
#include "ta_navigate_robot/temoto_action.h"
#include "temoto_robot_manager/robot_manager_interface.h"
#include "tf/tf.h"

#include <chrono>
#include <thread>

/* 
 * ACTION IMPLEMENTATION of TaNavigateRobot 
 */
class TaNavigateRobot : public TemotoAction
{
public:

/*
 * Function that gets invoked when the action is executed (REQUIRED)
 */
void executeTemotoAction()
{
  getInputParameters();
  rmi_.initialize();

  /*
   * Move the robot
   */
  geometry_msgs::PoseStamped target_pose;
  target_pose.header.frame_id = "map";
  target_pose.pose.position.x = in_param_pose_2d_x;
  target_pose.pose.position.y = in_param_pose_2d_y;
  target_pose.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, in_param_pose_2d_yaw);

  bool goal_reached{false};
  unsigned int retry_count{0};

  while (!goal_reached && actionOk() && retry_count < 3)
  try
  {
    TEMOTO_INFO_STREAM_("Sending a navigation goal to " << in_param_robot_name << " ...");
    rmi_.navigationGoal(in_param_robot_name, target_pose);
    TEMOTO_INFO_STREAM_("Done navigating");
    goal_reached = true;
  }
  catch(const resource_registrar::TemotoErrorStack &e)
  {
    TEMOTO_WARN_STREAM_("Caught an error: " << e.what() << "\nRequesting the same navigation goal again ... ");
    retry_count++;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  }

  if (!goal_reached)
  {
    std::string msg = "Unable to navigate robot '" + in_param_robot_name + "'. Make sure it is initialized first";
    throw CREATE_TEMOTO_ERROR(msg);
  }
}

// Default Constructor (REQUIRED)
TaNavigateRobot()
{
  std::cout << __func__ << " constructed\n";
}

// Destructor
~TaNavigateRobot()
{
  TEMOTO_INFO("Action instance destructed");
}

// Loads in the input parameters
void getInputParameters()
{
  in_param_robot_name = GET_PARAMETER("robot_name", std::string);
  in_param_pose_2d_x = GET_PARAMETER("pose_2d::x", double);
  in_param_pose_2d_y = GET_PARAMETER("pose_2d::y", double);
  in_param_pose_2d_yaw = GET_PARAMETER("pose_2d::yaw", double);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Class members
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

temoto_robot_manager::RobotManagerInterface rmi_;

// Declaration of input parameters
std::string in_param_robot_name;
double in_param_pose_2d_x;
double in_param_pose_2d_y;
double in_param_pose_2d_yaw;


}; // TaNavigateRobot class

/* REQUIRED BY CLASS LOADER */
CLASS_LOADER_REGISTER_CLASS(TaNavigateRobot, ActionBase);