//
// Created by eric1221bday on 4/7/18.
//

#include "kumquad/AprilSlam.h"
#include <geometry_msgs/PoseStamped.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

AprilSlam::AprilSlam(ros::NodeHandle &nh) :
    nh(nh) {
  initialize_callbacks();
}

void AprilSlam::initialize_callbacks() {
  detect_arr_sub = nh.subscribe("detections", 10, &AprilSlam::detection_callback, this);

  pose_pub = nh.advertise<geometry_msgs::PoseStamped>("pose", 10);
}

void AprilSlam::detection_callback(const apriltags::AprilTagDetections &detectionsMsg) {

  geometry_msgs::PoseStamped quad_pose;

  for (const auto &detection : detectionsMsg.detections) {
    if (detection.id == 0) {
      quad_pose.header.stamp = ros::Time::now();
      quad_pose.header.frame_id = "camera";
      tf2::Transform transform;
      tf2::fromMsg(detection.pose, transform);

      auto inv_transform = transform.inverse();

      tf2::toMsg(inv_transform, quad_pose.pose);

      pose_pub.publish(quad_pose);
    }
  }

}