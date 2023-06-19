cmake_minimum_required(VERSION 2.8.3)
project(tutorials_temoto_config)

# use c++11 standard
add_compile_options(-std=c++14)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  temoto_action_assistant
  temoto_process_manager
  temoto_robot_manager
  temoto_component_manager
)

catkin_package()

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

# Build component manager client
add_executable(component_manager_client
  src/component_manager_client.cpp
)

add_dependencies(component_manager_client 
  ${catkin_EXPORTED_TARGETS}
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
)

target_link_libraries(component_manager_client 
  ${catkin_LIBRARIES}
)

# component_string_0
add_executable(component_string_0
  src/component_string_0.cpp
)
add_dependencies(component_string_0
  ${catkin_EXPORTED_TARGETS} 
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
)
target_link_libraries(component_string_0
  ${catkin_LIBRARIES}
)

# component_string_1
add_executable(component_string_1
  src/component_string_1.cpp
)
add_dependencies(component_string_1
  ${catkin_EXPORTED_TARGETS} 
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
)
target_link_libraries(component_string_1
  ${catkin_LIBRARIES}
)

# component_string_2
add_executable(component_string_2
  src/component_string_2.cpp
)
add_dependencies(component_string_2
  ${catkin_EXPORTED_TARGETS} 
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
)
target_link_libraries(component_string_2
  ${catkin_LIBRARIES}
)

# Build process manager client
add_executable(process_manager_client
  src/process_manager_client.cpp
)

add_dependencies(process_manager_client 
  ${catkin_EXPORTED_TARGETS}
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
)

target_link_libraries(process_manager_client 
  ${catkin_LIBRARIES}
)

# Robot Manager Node
add_executable(rmi_command_robot
  src/rmi_command_robot.cpp
)

add_dependencies(rmi_command_robot 
  ${catkin_EXPORTED_TARGETS}
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
)

target_link_libraries(rmi_command_robot 
  ${catkin_LIBRARIES}
)
