
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
#include "ta_robot1_viz/temoto_action.h"
#include "temoto_visualization_manager/visualization_manager_interface.h"

/* 
 * ACTION IMPLEMENTATION of TaRobot1Viz 
 */
class TaRobot1Viz : public TemotoAction
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
  getInputParameters();
  vmi_.initialize();

  TEMOTO_INFO_STREAM("Showing robot '" << in_param_robot1_name << "' in RViz ...");
  std::string robot_description_rviz_config = "{Robot Description: " + in_param_robot1_description + "}";
  vmi_.loadRvizPlugin("rviz/RobotModel", "", robot_description_rviz_config, in_param_robot1_name + " model");
  TEMOTO_INFO_STREAM("Robot '" << in_param_robot1_name << "' visualized");
  
  out_param_robot1_name = in_param_robot1_name;
  setOutputParameters();
}

// Destructor
~TaRobot1Viz()
{
  TEMOTO_INFO("Action instance destructed");
}

// Loads in the input parameters
void getInputParameters()
{
  in_param_robot1_description = GET_PARAMETER("robot1_description", std::string);
  in_param_robot1_name = GET_PARAMETER("robot1_name", std::string);
}

// Sets the output parameters which can be passed to other actions
void setOutputParameters()
{
  SET_PARAMETER("robot1_name", "string", out_param_robot1_name);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Class members
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
temoto_visualization_manager::VisualizationManagerInterface vmi_;

// Declaration of input parameters
std::string in_param_robot1_description;
std::string in_param_robot1_name;

// Declaration of output parameters
std::string out_param_robot1_name;


}; // TaRobot1Viz class

/* REQUIRED BY CLASS LOADER */
CLASS_LOADER_REGISTER_CLASS(TaRobot1Viz, ActionBase);
