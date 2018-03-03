#include <ros/ros.h>

int main(int argc, char** argv) {

  ros::init(argc, argv, "kumquad");
  ros::NodeHandle nh;


  ros::spin();
}