//
// Created by eric1221bday on 4/7/18.
//

#ifndef KUMQUAD_APRILSLAM_H
#define KUMQUAD_APRILSLAM_H

#include <ros/ros.h>
#include <apriltags/AprilTagDetections.h>

class AprilSlam {
 private:
  ros::NodeHandle nh;
  ros::Subscriber detect_arr_sub;
  ros::Publisher pose_pub;

 public:
  AprilSlam(ros::NodeHandle &nh);

  void initialize_callbacks();

  void detection_callback(const apriltags::AprilTagDetections &detectionsMsg);
};

#endif //KUMQUAD_APRILSLAM_H
