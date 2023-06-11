# RPSTONE - the ref's gonna stone you

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

### setup

```bash
cd gesture_detection && npm install
```

A) With OpenPose installed and usb_cam running:
```bash
roslaunch ros_openpose run.launch camera:=nodepth
```
B) Use a rosbag containing openpose keypoints:
```bash
# Bag that contains /frame messages containing hand keypoints (Openpose)
rosbag play --loop rpstone/bags/rps.bag
```

### gesture classifier node:

```bash
roslaunch rosbridge_server rosbridge_websocket.launch 
```

```bash
cd gesture_detection && npm run start
```