//
// Created by eric1221bday on 4/7/18.
//

#include "kumquad/AprilSlam.h"
#include <geometry_msgs/PoseStamped.h>

AprilSlam::AprilSlam(ros::NodeHandle &nh) :
    nh(nh) {
  initialize_callbacks();
}

void AprilSlam::initialize_callbacks() {
  detect_arr_sub = nh.subscribe<apriltags_ros::AprilTagDetectionArray>("detections", 10, &AprilSlam::detection_callback, this);

  pose_pub = nh.advertise<geometry_msgs::PoseStamped>("pose", 10);
}

void AprilSlam::detection_callback(apriltags_ros::AprilTagDetectionArrayConstPtr &detectionsMsg) {

  geometry_msgs::PoseStamped quad_pose;

  for (auto const &detection : detectionsMsg->detections) {
    if (detection.id == 0) {
      quad_pose.header.stamp = ros::Time::now();
      quad_pose.pose = detection.pose.pose;
    }
  }

  pose_pub.publish(quad_pose);
}