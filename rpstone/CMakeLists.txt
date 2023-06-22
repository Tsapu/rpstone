cmake_minimum_required(VERSION 2.8.3)
project(rpstone)

# use c++11 standard
add_compile_options(-std=c++14)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  temoto_action_assistant
  ros_openpose # comment this out if you don't have it and run from bag
  std_msgs
  message_generation
)

add_message_files(
  FILES
  Gesture.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)


catkin_package(
  CATKIN_DEPENDS message_runtime temoto_component_manager
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(rptwist src/twist_cmd.cpp)
target_link_libraries(rptwist ${catkin_LIBRARIES})