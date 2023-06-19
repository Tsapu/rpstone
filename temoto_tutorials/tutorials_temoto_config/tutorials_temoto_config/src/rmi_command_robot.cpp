#include "ros/ros.h"
#include "temoto_robot_manager/robot_manager_interface.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "rm_load_robot");
  ros::AsyncSpinner spinner(4); // Use 4 threads
  spinner.start();

  std::string robot_name = "vaultbot_sim"; 
  
  /*
   * Create a Robot Manager Interface object that provides a simplified
   * API for communicating with the Robot Manager. 
   */
  temoto_robot_manager::RobotManagerInterface rmi(true);

  /*
   *  Load the robot 
   */
  ROS_INFO("Loading robot '%s' ...", robot_name.c_str());   
  rmi.loadRobot(robot_name);
  ROS_INFO("Robot loaded");

  /*
   *  Send a navigation goal 
   */ 
  geometry_msgs::PoseStamped target_pose;
  target_pose.header.frame_id = "map";
  target_pose.pose.position.x = -3.0;
  target_pose.pose.position.y = 1.0;
  target_pose.pose.orientation.x = 0.0;
  target_pose.pose.orientation.y = 0.0;
  target_pose.pose.orientation.z = 0.0;
  target_pose.pose.orientation.w = 1.0;

  for (unsigned int retry_count{0}; retry_count < 3; retry_count++)
  try
  {
    ROS_INFO("Sending a navigation goal ...");
    rmi.navigationGoal(robot_name, target_pose);
    ROS_INFO("Done");
    break;
  }
  catch(const resource_registrar::TemotoErrorStack &e)
  {
    ROS_WARN_STREAM("Caught an error: " << e.what() << "\nRequesting the same navigation goal again ... ");
    ros::Duration(2).sleep();
  }

  /*
   *  Send a manipulation goal 
   */
  geometry_msgs::PoseStamped manip_target_pose;
  manip_target_pose.header.frame_id = "base_link";
  manip_target_pose.pose.position.x = 0.570;
  manip_target_pose.pose.position.y = -0.720;
  manip_target_pose.pose.position.z = 0.711;
  manip_target_pose.pose.orientation.x = -0.514;
  manip_target_pose.pose.orientation.y = 0.767;
  manip_target_pose.pose.orientation.z = -0.342;
  manip_target_pose.pose.orientation.w = -0.175;
  
  ROS_INFO("Sending a manipulation goal ...");
  rmi.planManipulation(robot_name, "r_arm", manip_target_pose);
  rmi.executePlan(robot_name);
  ROS_INFO("Done");

  return 0;
}