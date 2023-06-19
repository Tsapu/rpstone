
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
#include "ta_move_manipulator_eef/temoto_action.h"
#include "temoto_robot_manager/robot_manager_interface.h"

/* 
 * ACTION IMPLEMENTATION of TaMoveManipulatorEef 
 */
class TaMoveManipulatorEef : public TemotoAction
{
public:

/*
 * Function that gets invoked only once (when the action is initialized) throughout the action's lifecycle
 */
void initializeTemotoAction()
{
  getInputParameters();
  rmi_.initialize();
  rmi_.loadRobot(in_param_robot_name);
  TEMOTO_INFO_STREAM("Action initialized");
}

/*
 * Function that gets invoked when the action is executed (REQUIRED)
 */
void executeTemotoAction()
{  
  geometry_msgs::PoseStamped target_pose;
  target_pose.header.frame_id = "base_link";
  target_pose.pose.position.x = in_param_pose_quat_position_x;
  target_pose.pose.position.y = in_param_pose_quat_position_y;
  target_pose.pose.position.z = in_param_pose_quat_position_z;

  target_pose.pose.orientation.x = in_param_pose_quat_orientation_x;
  target_pose.pose.orientation.y = in_param_pose_quat_orientation_y;
  target_pose.pose.orientation.z = in_param_pose_quat_orientation_z;
  target_pose.pose.orientation.w = in_param_pose_quat_orientation_w;

  rmi_.planManipulation(in_param_robot_name, in_param_eef_name, target_pose);  
  rmi_.executePlan(in_param_robot_name);
}

// Destructor
~TaMoveManipulatorEef()
{
  TEMOTO_INFO("Action instance destructed");
}

// Loads in the input parameters
void getInputParameters()
{
  in_param_robot_name = GET_PARAMETER("robot_name", std::string);
  in_param_eef_name = GET_PARAMETER("eef_name", std::string);
  in_param_pose_quat_orientation_w = GET_PARAMETER("pose_quat::orientation::w", double);
  in_param_pose_quat_orientation_x = GET_PARAMETER("pose_quat::orientation::x", double);
  in_param_pose_quat_orientation_y = GET_PARAMETER("pose_quat::orientation::y", double);
  in_param_pose_quat_orientation_z = GET_PARAMETER("pose_quat::orientation::z", double);
  in_param_pose_quat_position_x = GET_PARAMETER("pose_quat::position::x", double);
  in_param_pose_quat_position_y = GET_PARAMETER("pose_quat::position::y", double);
  in_param_pose_quat_position_z = GET_PARAMETER("pose_quat::position::z", double);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Class members
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Declaration of input parameters
std::string in_param_robot_name;
std::string in_param_eef_name;
double in_param_pose_quat_orientation_w;
double in_param_pose_quat_orientation_x;
double in_param_pose_quat_orientation_y;
double in_param_pose_quat_orientation_z;
double in_param_pose_quat_position_x;
double in_param_pose_quat_position_y;
double in_param_pose_quat_position_z;

// Other class members
temoto_robot_manager::RobotManagerInterface rmi_;


}; // TaMoveManipulatorEef class

/* REQUIRED BY CLASS LOADER */
CLASS_LOADER_REGISTER_CLASS(TaMoveManipulatorEef, ActionBase);
