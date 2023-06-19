
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
#include "ta_initialize_robot/temoto_action.h"
#include "temoto_robot_manager/robot_manager_interface.h"

/* 
 * ACTION IMPLEMENTATION of TaInitializeRobot 
 */
class TaInitializeRobot : public TemotoAction
{
public:

/*
 * Function that gets invoked only once (when the action is initialized) throughout the action's lifecycle
 */
void initializeTemotoAction()
{
  TEMOTO_INFO_STREAM("Action initialized");
}

/*
 * Function that gets invoked when the action is executed (REQUIRED)
 */
void executeTemotoAction()
{
  getInputParameters();
  rmi_.initialize();

  TEMOTO_INFO_STREAM("loading " << in_param_robot_name << "...");
  rmi_.loadRobot(in_param_robot_name);

  TEMOTO_INFO_STREAM("trying to get config of '" << in_param_robot_name << "' ...");
  YAML::Node robot_config = rmi_.getRobotConfig(in_param_robot_name);
  TEMOTO_INFO_STREAM("Config of robot '" << in_param_robot_name << "': " << robot_config);

  out_param_robot_name = in_param_robot_name;
  out_param_robot_description = "/" + robot_config["robot_absolute_namespace"].as<std::string>()
    + "/robot_description";

  TEMOTO_INFO_STREAM(in_param_robot_name << " initialized");

  setOutputParameters();
}

// Destructor
~TaInitializeRobot()
{
  TEMOTO_INFO("Action instance destructed");
}

// Loads in the input parameters
void getInputParameters()
{
  in_param_robot_name = GET_PARAMETER("robot_name", std::string);
}

// Sets the output parameters which can be passed to other actions
void setOutputParameters()
{
  SET_PARAMETER("robot_name", "string", out_param_robot_name);
  SET_PARAMETER("robot_description", "string", out_param_robot_description);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Class members
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

temoto_robot_manager::RobotManagerInterface rmi_;

// Declaration of input parameters
std::string in_param_robot_name;

// Declaration of output parameters
std::string out_param_robot_name;
std::string out_param_robot_description;


}; // TaInitializeRobot class

/* REQUIRED BY CLASS LOADER */
CLASS_LOADER_REGISTER_CLASS(TaInitializeRobot, ActionBase);
