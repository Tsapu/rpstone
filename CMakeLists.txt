cmake_minimum_required(VERSION 2.8.3)
project(rpstone)

find_package(catkin REQUIRED COMPONENTS
  roscpp
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
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime  # Add message_runtime
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)


# add_executable(rpstone_node src/rpstone_node.cpp)

# target_link_libraries(rpstone_node
#   ${catkin_LIBRARIES}
# )

# install(TARGETS rpstone_node
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

add_executable(hand_detector rpstone/src/rpstone.cpp)
target_link_libraries(hand_detector ${catkin_LIBRARIES})