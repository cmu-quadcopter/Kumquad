# Kumquad
April Tag based Localization for MAV

## Workspace Setup
```bash
mkdir -p april_ws/src && cd april_ws
wstool init src
wstool merge -t src https://raw.githubusercontent.com/cmu-quadcopter/Kumquad/master/.rosinstall
wstool update -t src
rosdep update
rosdep install --from-paths src --ignore-src -r -y

catkin init
```

## Workspace Build
```
catkin build
```

## Usage
### Run with bag file
```
roslaunch kumquad iris_bluefox_fisheye.launch live:=false
```
### Run with live camera
```
roslaunch kumquad iris_bluefox_fisheye.launch
```
