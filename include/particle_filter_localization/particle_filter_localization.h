#ifndef _PARTICLE_FILTER_LOCALIZATION_H_
#define _PARTICLE_FILTER_LOCALIZATION_H_

#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <nav_sim/LandmarkInfoArray.h>
#include <ros/ros.h>

#include <random>

#include <Eigen/Core>

#include <particle_filter_localization/particle_filter.h>

class ParticleFilterLocalization
{
public:
  ParticleFilterLocalization();
  ~ParticleFilterLocalization() = default;

private:
  void poseCallback(const geometry_msgs::PoseStamped & msg);
  void twistCallback(const geometry_msgs::TwistStamped & msg);
  void initialposeCallback(const geometry_msgs::PoseWithCovarianceStamped & msg);
  void observationCallback(const nav_sim::LandmarkInfoArray & msg);

  void publishParticles(const ros::Time stamp);

  void update(const double velocity, const double omega, const double dt);

  void observationUpdate(const nav_sim::LandmarkInfoArray observation);

private:
  ros::NodeHandle nh_{};
  ros::NodeHandle pnh_{"~"};

  ros::Time latest_stamp_;

  ros::Subscriber initialpose_subscriber_;
  ros::Subscriber pose_subscriber_;
  ros::Subscriber twist_subscriber_;
  ros::Subscriber observation_subscriber_;
  ros::Publisher particle_publisher_;

  geometry_msgs::TwistStamped twist_;
  geometry_msgs::TwistStamped prev_twist_;

  boost::shared_ptr<ParticleFilter> particle_filter_ptr_;

  int particle_num_;
  std::string frame_id_;

  double sigma_vv_;
  double sigma_vw_;
  double sigma_wv_;
  double sigma_ww_;
  Eigen::Vector4d motion_noise_std_vec_;
};

#endif
