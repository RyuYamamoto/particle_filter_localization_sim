#ifndef _UTILS_H_
#define _UTILS_H_

#include <geometry_msgs/Pose.h>
#include <tf/tf.h>
#include <Eigen/Core>

namespace utils
{
Eigen::VectorXd convertToVector(const geometry_msgs::Pose pose)
{
  Eigen::VectorXd vec(3);

  vec(0) = pose.position.x;
  vec(1) = pose.position.y;

  tf::Quaternion q(pose.orientation.x, pose.orientation.y, pose.orientation.z, pose.orientation.w);
  tf::Matrix3x3 m(q);
  double r, p, y;
  m.getRPY(r, p, y);
  vec(2) = y;

  return vec;
}

geometry_msgs::Pose convertToPose(const Eigen::VectorXd vec)
{
  geometry_msgs::Pose pose;
  pose.position.x = vec(0);
  pose.position.y = vec(1);
  pose.position.z = 0.0;
  tf::Quaternion quat;
  quat.setRPY(0.0, 0.0, vec(2));
  pose.orientation.x = quat.x();
  pose.orientation.y = quat.y();
  pose.orientation.z = quat.z();
  pose.orientation.w = quat.w();

  return pose;
}
}  // namespace utils

#endif
