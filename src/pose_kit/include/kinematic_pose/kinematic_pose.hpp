/**
 * Kinematic pose library, based on Eigen geometry types.
 *
 * Roberto Masocco <robmasocco@gmail.com>
 * Intelligent Systems Lab <isl.torvergata@gmail.com>
 *
 * April 14, 2023
 */

#ifndef DRONE_STATE__KINEMATIC_POSE_HPP_
#define DRONE_STATE__KINEMATIC_POSE_HPP_

#include "visibility_control.h"

#include <stdexcept>

#include <Eigen/Geometry>
#include <unsupported/Eigen/EulerAngles>

#include <dua_interfaces/msg/euler_pose_stamped.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>

#include <pose/pose.hpp>

namespace DroneState
{

/**
 * Represents position, orientation, and velocity of an autonomous agent.
 */
class KINEMATIC_POSE_PUBLIC KinematicPose : public Pose
{
public:
  /* Constructors. */
  KinematicPose() {}
  KinematicPose(const KinematicPose & kp);
  KinematicPose(
    double x, double y, double z,
    double vx, double vy, double vz);
  KinematicPose(
    const Eigen::Quaterniond & q,
    const Eigen::Vector3d & angular_vel);
  KinematicPose(
    const Eigen::EulerAnglesXYZd & rpy_angles,
    const Eigen::Vector3d & angular_vel);
  KinematicPose(
    double x, double y, double z,
    double vx, double vy, double vz,
    double heading,
    const std::array<double, 36> & cov = std::array<double, 36>{});
  KinematicPose(
    const Eigen::Vector3d & pos,
    const Eigen::Quaterniond & q,
    const Eigen::EulerAnglesXYZd & rpy_angles,
    const Eigen::Vector3d & vel,
    const Eigen::Vector3d & angular_vel,
    const std::array<double, 36> & cov = std::array<double, 36>{},
    const std::array<double, 36> & twist_cov = std::array<double, 36>{});
  KinematicPose(const EulerPoseStamped & msg);
  KinematicPose(Pose p)
  : Pose(std::move(p)) {}

  /* Destructor. */
  virtual ~KinematicPose() {}

  /* Getters. */
  Eigen::Vector3d get_velocity() const;
  Eigen::Vector3d get_angular_velocity() const;
  std::array<double, 36> get_twist_covariance() const;

  /* Setters. */
  void set_velocity(const Eigen::Vector3d & vel);
  void set_angular_velocity(const Eigen::Vector3d & angular_vel);
  void set_twist_covariance(const std::array<double, 36> & twist_cov);

  /* Geometric operations. */
  KinematicPose operator*(const KinematicPose & kp) const;

  /* Assignment operators. */
  KinematicPose & operator=(const KinematicPose & kp);
  KinematicPose & operator=(KinematicPose && kp);

protected:
  /* Internal data. */
  Eigen::Vector3d velocity_ = {0.0, 0.0, 0.0}; // [m/s]
  Eigen::Vector3d angular_velocity_ = {0.0, 0.0, 0.0}; // [rad/s]
  std::array<double, 36> twist_covariance_{};
};

}  // namespace DroneState

#endif  // DRONE_STATE__KINEMATIC_POSE_HPP_