#include <ros/ros.h>
#include "kumquad/AprilSlam.h"

int main(int argc, char** argv) {

  ros::init(argc, argv, "kumquad");
  ros::NodeHandle nh;
  AprilSlam slam(nh);

  ros::spin();
}