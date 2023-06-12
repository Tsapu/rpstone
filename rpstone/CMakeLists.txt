cmake_minimum_required(VERSION 2.8.3)
project(rpstone)

# use c++11 standard
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  temoto_action_assistant
  ros_openpose
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
  CATKIN_DEPENDS message_runtime
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(hand_detector src/rpstone.cpp)
target_link_libraries(hand_detector ${catkin_LIBRARIES})

add_executable(gesture_confirmation_node src/gesture_confirmation_node.cpp)
target_link_libraries(gesture_confirmation_node ${catkin_LIBRARIES})