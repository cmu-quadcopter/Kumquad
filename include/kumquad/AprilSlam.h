//
// Created by eric1221bday on 4/7/18.
//

#ifndef KUMQUAD_APRILSLAM_H
#define KUMQUAD_APRILSLAM_H

#include <ros/ros.h>
#include <apriltags/AprilTagDetections.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>

class AprilSlam {
 private:
  ros::NodeHandle nh;
  ros::Subscriber detect_arr_sub;
  ros::Publisher pose_pub;
  geometry_msgs::TransformStamped cam_pos;

 public:
  AprilSlam(ros::NodeHandle &nh);

  void initialize_callbacks();

  void detection_callback(const apriltags::AprilTagDetections &detectionsMsg);
};

#endif //KUMQUAD_APRILSLAM_H
