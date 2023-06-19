# temoto_tutorials
Replication package that goes along with the tutorials in [TeMoto wiki](https://github.com/temoto-framework/temoto/wiki)

## Installation:

First install the dependencies:
```bash
sudo apt install gazebo11 ros-noetic-gazebo-ros ros-noetic-gazebo-ros-control ros-noetic-gazebo-plugins ros-noetic-lms1xx ros-noetic-robot-localization ros-noetic-interactive-marker-twist-server ros-noetic-twist-mux ros-noetic-map-server ros-noetic-amcl ros-noetic-move-base ros-noetic-joint-trajectory-controller ros-noetic-joint-state-controller ros-noetic-diff-drive-controller ros-noetic-dwa-local-planner ros-noetic-controller-manager ros-noetic-serial
```

Then clone this package and build it:

``` bash
cd <your-catkin-workspace>/src
git clone --recursive https://github.com/temoto-framework-demos/temoto_tutorials.git
catkin build
source devel/setup.bash
```

## Test if the robot simulation is properly set up

Open a terminal and launch the husky simulation:

```bash 
roslaunch husky_dual_ur5_config husky_dual_ur5_sim.launch
```

You should see the Gazebo sim opening up. If you are launching it for the first time, then
it might take some time for Gazebo to download the world models. Once the world is loaded, you 
should see the robot. There might be couple of warnings in the terminal about `No p gain specified for pid` 
or `Failed to meet update rate!` but that's nothing to worry about.

Next, open a second terminal and launch the visualization:
```bash
roslaunch husky_dual_ur5_config husky_dual_ur5_sim_viz.launch
```

RViz should pop up and you should see the map, robot and lidar data. Use the `2D Nav Goal` tool to move the robot somewhere within the map and also try to move the manipulators via the interactive marker. If the robot performs sucessfully, then the simulation is set up properly. 