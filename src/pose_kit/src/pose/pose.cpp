/**
 * Pose library implementation.
 *
 * Roberto Masocco <robmasocco@gmail.com>
 * Intelligent Systems Lab <isl.torvergata@gmail.com>
 *
 * April 13, 2023
 */

#include <pose/pose.hpp>

namespace PoseKit
{

/**
 * @brief Default constructor.
 */
Pose::Pose()
{}

/**
 * @brief Copy constructor.
 *
 * @param p Pose to copy.
 */
Pose::Pose(const Pose & p)
{
  set_position(p.get_position());
  set_attitude(p.get_attitude());
  set_rpy(p.get_rpy());
  set_pose_covariance(p.get_pose_covariance());
}

/**
 * @brief Constructor with initial position.
 *
 * @param x Initial X position [m].
 * @param y Initial Y position [m].
 * @param z Initial Z position [m].
 */
Pose::Pose(double x, double y, double z)
{
  set_position(Eigen::Vector3d(x, y, z));
  set_attitude(Eigen::Quaterniond::Identity());
  set_rpy({0.0, 0.0, 0.0});
}

/**
 * @brief Constructor with initial attitude.
 *
 * @param q Initial attitude quaternion.
 */
Pose::Pose(const Eigen::Quaterniond & q)
{
  set_position(Eigen::Vector3d(0.0, 0.0, 0.0));
  set_attitude(q);
  set_rpy({0.0, 0.0, 0.0});
}

/**
 * @brief Constructor with initial euler angles.
 *
 * @param rpy_angles Initial euler angles [rad] in [-PI +PI] (may also be an array).
 */
Pose::Pose(const Eigen::EulerAnglesXYZd & rpy_angles)
{
  set_position(Eigen::Vector3d(0.0, 0.0, 0.0));
  set_attitude(Eigen::Quaterniond(rpy_angles));
  set_rpy(rpy_angles);
}

/**
 * @brief Constructor with initial position and heading.
 *
 * @param x Initial X position [m].
 * @param y Initial Y position [m].
 * @param z Initial Z position [m].
 * @param heading Initial heading [rad] in [-PI +PI].
 * @param cov Initial pose covariance.
 */
Pose::Pose(
  double x, double y, double z, double heading,
  const std::array<double, 36> & cov)
{
  set_position(Eigen::Vector3d(x, y, z));
  set_attitude(
    Eigen::Quaterniond(
      Eigen::AngleAxisd(0.0, Eigen::Vector3d::UnitX()) *
      Eigen::AngleAxisd(0.0, Eigen::Vector3d::UnitY()) *
      Eigen::AngleAxisd(heading, Eigen::Vector3d::UnitZ())));
  set_rpy({0.0, 0.0, heading});
  set_pose_covariance(cov);
}

/**
 * @brief Constructor with initial position, attitude and euler angles.
 *
 * @param pos Initial position [m].
 * @param q Initial attitude quaternion.
 * @param cov Initial pose covariance.
 */
Pose::Pose(
  const Eigen::Vector3d & pos,
  const Eigen::Quaterniond & q,
  const std::array<double, 36> & cov)
{
  set_position(pos);
  set_attitude(q);
  set_rpy(Eigen::EulerAnglesXYZd(q));
  set_pose_covariance(cov);
}

/**
 * @brief Constructor that builds from an EulerPoseStamped ROS message.
 *
 * @param msg ROS message to build from.
 */
Pose::Pose(const EulerPoseStamped & msg)
{
  set_position(
    Eigen::Vector3d(
      msg.pose.position.x,
      msg.pose.position.y,
      msg.pose.position.z));
  set_attitude(
    Eigen::Quaterniond(
      msg.pose.orientation.w,
      msg.pose.orientation.x,
      msg.pose.orientation.y,
      msg.pose.orientation.z));
  set_rpy({msg.roll, msg.pitch, msg.yaw});
}

/**
 * @brief Copy assignment operator.
 *
 * @param p Pose to copy.
 */
Pose & Pose::operator=(const Pose & p)
{
  set_position(p.get_position());
  set_attitude(p.get_attitude());
  set_rpy(p.get_rpy());
  set_pose_covariance(p.get_pose_covariance());
  return *this;
}

/**
 * @brief Move assignment operator.
 *
 * @param p Pose to move.
 */
Pose & Pose::operator=(Pose && p)
{
  set_position(p.get_position());
  set_attitude(p.get_attitude());
  set_rpy(p.get_rpy());
  set_pose_covariance(p.get_pose_covariance());
  return *this;
}

/**
 * @brief Default destructor.
 */
Pose::~Pose()
{}

/**
 * @brief Converts to an EulerPoseStamped ROS message (does not fill other fields).
 */
EulerPoseStamped Pose::to_euler_pose_stamped()
{
  EulerPoseStamped msg{};
  msg.pose.position.x = position_(0);
  msg.pose.position.y = position_(1);
  msg.pose.position.z = position_(2);
  msg.pose.orientation.w = attitude_.w();
  msg.pose.orientation.x = attitude_.x();
  msg.pose.orientation.y = attitude_.y();
  msg.pose.orientation.z = attitude_.z();
  msg.roll = rpy_.alpha();
  msg.pitch = rpy_.beta();
  msg.yaw = rpy_.gamma();
  return msg;
}

/**
 * @brief Converts to a PoseStamped ROS message (does not fill other fields).
 */
geometry_msgs::msg::PoseStamped Pose::to_pose_stamped()
{
  geometry_msgs::msg::PoseStamped msg{};
  msg.pose.position.x = position_(0);
  msg.pose.position.y = position_(1);
  msg.pose.position.z = position_(2);
  msg.pose.orientation.w = attitude_.w();
  msg.pose.orientation.x = attitude_.x();
  msg.pose.orientation.y = attitude_.y();
  msg.pose.orientation.z = attitude_.z();
  return msg;
}

/**
 * @brief Position getter.
 *
 * @return Position [m].
 */
Eigen::Vector3d Pose::get_position() const
{
  return position_;
}

/**
 * @brief Attitude getter.
 *
 * @return Attitude quaternion.
 */
Eigen::Quaterniond Pose::get_attitude() const
{
  return attitude_;
}

/**
 * @brief Euler angles getter.
 *
 * @return Euler angles [rad] in [-PI +PI].
 */
Eigen::EulerAnglesXYZd Pose::get_rpy() const
{
  return rpy_;
}

/**
 * @brief Rotation getter.
 *
 * @return Rotation (as Eigen transformation).
 */
Eigen::AngleAxisd Pose::get_rotation() const
{
  return Eigen::AngleAxisd(attitude_);
}

/**
 * @brief Translation getter.
 *
 * @return Translation (as Eigen transformation).
 */
Eigen::Translation3d Pose::get_translation() const
{
  return Eigen::Translation3d(position_);
}

/**
 * @brief Isometry getter.
 *
 * @return Isometry.
 */
Eigen::Isometry3d Pose::get_isometry() const
{
  Eigen::Isometry3d isometry = Eigen::Isometry3d::Identity();
  isometry.rotate(this->get_rotation());
  isometry.pretranslate(this->get_translation().vector());
  return isometry;
}

/**
 * @brief Pose covariance getter.
 *
 * @return Pose covariance.
 */
std::array<double, 36> Pose::get_pose_covariance() const
{
  return pose_covariance_;
}

/**
 * @brief Position setter.
 *
 * @param pos Position [m].
 */
void Pose::set_position(const Eigen::Vector3d & pos)
{
  position_ = pos;
}

/**
 * @brief Attitude setter.
 *
 * @param q Attitude quaternion.
 */
void Pose::set_attitude(const Eigen::Quaterniond & q)
{
  attitude_ = q.normalized();
}

/**
 * @brief Euler angles setter.
 *
 * @param rpy_angles Euler angles [rad] in [-PI +PI].
 */
void Pose::set_rpy(const Eigen::EulerAnglesXYZd & rpy_angles)
{
  rpy_ = rpy_angles;
}

/**
 * @brief Pose covariance setter.
 *
 * @param cov Pose covariance.
 */
void Pose::set_pose_covariance(const std::array<double, 36> & cov)
{
  pose_covariance_ = cov;
}

/**
 * @brief Right-multiplies by a given pose.
 *
 * @param p Transform pose.
 * @return Transformed pose.
 *
 * @throws InvalidArgument if the coordinate frame is not coherent.
 */
Pose Pose::operator*(const Pose & p) const
{
  // TODO Check that the coordinate frame is coherent

  // Compute the right transformation using Eigen
  Eigen::Isometry3d new_isometry = this->get_isometry() * p.get_isometry();
  Eigen::Vector3d new_position(new_isometry.translation());
  Eigen::Quaterniond new_attitude(new_isometry.rotation());

  // Build a new pose
  // TODO Set header
  Pose new_pose{};
  new_pose.set_position(new_position);
  new_pose.set_attitude(new_attitude);
  new_pose.set_rpy(Eigen::EulerAnglesXYZd(new_attitude));
  new_pose.set_pose_covariance(this->get_pose_covariance());
  return new_pose;
}

}  // namespace PoseKit
