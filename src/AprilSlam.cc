//
// Created by eric1221bday on 4/7/18.
//

#include "kumquad/AprilSlam.h"
#include <geometry_msgs/PoseStamped.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

AprilSlam::AprilSlam(ros::NodeHandle &nh) :
    nh(nh) {
  initialize_callbacks();

  tf2_ros::Buffer tf_buffer;
  tf2_ros::TransformListener listener(tf_buffer);
  bool got_transform = false;

  while(!got_transform) {
    try {

      cam_pos = tf_buffer.lookupTransform("fcu", "camera", ros::Time(0));
      got_transform = true;

    } catch(tf2::TransformException &ex) {

      ROS_WARN("%s", ex.what());
      ros::Duration(1.0).sleep();
    }
  }

}

void AprilSlam::initialize_callbacks() {
  detect_arr_sub = nh.subscribe("detections", 10, &AprilSlam::detection_callback, this);

  pose_pub = nh.advertise<geometry_msgs::PoseStamped>("pose", 10);
}

void AprilSlam::detection_callback(const apriltags::AprilTagDetections &detectionsMsg) {

  static tf2_ros::TransformBroadcaster broadcaster;
  geometry_msgs::TransformStamped map_to_cam;
  map_to_cam.header.stamp = ros::Time::now();
  map_to_cam.header.frame_id = "map";
  map_to_cam.child_frame_id = "camera";

  for (const auto &detection : detectionsMsg.detections) {
    if (detection.id == 0) {
      tf2::Transform transform;
      tf2::fromMsg(detection.pose, transform);

      auto inv_transform = transform.inverse();

      map_to_cam.transform = tf2::toMsg(inv_transform);

      broadcaster.sendTransform(map_to_cam);
    }
  }

}