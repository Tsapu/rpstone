# RPSTONE

## What is this?

![Scrapapa](./doc/mediapipe_finger_keypoints.png)

So Openpose cannot detect *only* the hand keypoints without providing bounding boxes (aditional hand detector on top), so it needs the whole body (of both players). Mediapipe is nice, but it cannot detect multiple persons by default (?).

The gesture_detection is done in nodejs, because the classifier lib works nicely, could not find easy alternatives for c++.

## Requirements
- ROS Noetic
- Nodejs v16
- [Openpose](https://github.com/CMU-Perceptual-Computing-Lab/openpose)
- [ros_openpose](https://github.com/ravijo/ros_openpose)
- [TeMoto](https://github.com/temoto-framework/temoto/wiki) (coming soon)
- rosbridge (`sudo apt install ros-noetic-rosbridge-server`)
- sox
- libsox-fmt-mp3

### setup

```bash
cd gesture_detector/src && npm install
catkin build
```

### usage example
```bash
roslaunch usb_cam usb_cam-test.launch
```

```bash
roslaunch ros_openpose run.launch camera:=nodepth
```

```bash
roslaunch gesture_detector classifier_nodepth.launch
```

### example results from a rosbag:

```bash
# Bag that contains /frame messages containing hand keypoints (Openpose) and /rps_gestures from the classifer
rosbag play --loop rpstone/bags/rps.bag
```

## Ok, let's temoto
```bash
roslaunch rpstone temoto.launch temoto_namespace:=rpstone
```

Launch the component pipe:
```bash
rosrun temoto_action_engine umrf_graph_publisher ta_rps_pipe.umrfg.json rpstone
```

To work with a rosbag instead of OpenPose, plase make sure that the main pipe method at `rpstone/config/pipes.yaml` is commented out which will make the program run from a rosbag

<br/>

![Scrapapa2](./doc/arch.png)
![Scrapapa3](./doc/pipe.png)

## Todo (updated: 11.06)
- [x] Add gesture classifier node
- [x] Implement component pipe


<br/>
<br/>
__________________________________________________________________________________________