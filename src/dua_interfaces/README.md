# dua_interfaces

ROS 2 interfaces for the Distributed Unified Architecture, aimed at robotics projects and more.

## Contents

Refer to the individual interface files for more information.

### Messages

- [x] [`CommandResultStamped`](msg/CommandResultStamped.msg): Result of a command execution, useful to be included in high-level communications like services and actions, with a ROS header.
- [x] [`EulerAttitudeSetpoint`](msg/EulerAttitudeSetpoint.msg): Setpoint for an Euler attitude controller.
- [x] [`EulerPoseStamped`](msg/EulerPoseStamped.msg): Pose with Euler angles, avoids the need for a quaternion to Euler conversion.
- [x] [`PointCloud2WithROI`](msg/PointCloud2WithROI.msg): Point cloud with a region of interest.
- [x] [`PositionSetpoint`](msg/PositionSetpoint.msg): Setpoint for a position controller.
- [x] [`RatesSetpoint`](msg/RatesSetpoint.msg): Setpoint for a roll-pitch-yaw rates controller.
- [x] [`RegionOfInterest`](msg/RegionOfInterest.msg): Region of interest, useful for image processing and spatial mapping.
- [x] [`Target`](msg/Target.msg): Target, useful for target detection and tracking using a variety of sensors.
- [x] [`TargetArray`](msg/TargetArray.msg): Array of `Target` messages, useful when a sensor can detect multiple targets at once.
- [x] [`TargetID`](msg/TargetID.msg): Target ID, part of the `Target` message.
- [x] [`TargetIDArray`](msg/TargetIDArray.msg): Array of `TargetID` messages.
- [x] [`VelocitySetpoint`](msg/VelocitySetpoint.msg): Setpoint for a velocity controller.
- [x] [`VisualTargets`](msg/VisualTargets.msg): Array of `Target` messages paired with a `sensor_msgs/Image` that shows them.

### Actions

- [x] [`Arm`](action/Arm.action): Arms a component.
- [x] [`Disarm`](action/Disarm.action): Disarm a component.
- [x] [`Landing`](action/Landing.action): Performs a landing operation on a flying robot.
- [x] [`Navigate`](action/Navigate.action): Navigates a robot to a target position.
- [x] [`Reach`](action/Reach.action): Reaches a target pose in 3D space with a robot.
- [x] [`Takeoff`](action/Takeoff.action): Performs a takeoff operation on a flying robot.
- [x] [`Turn`](action/Turn.action): Turns a robot to a target yaw angle.

## Requirements

Builds on ROS 2 Humble Hawksbill.

See [`package.xml`](package.xml) for more information.

---

## License

This work is licensed under the GNU General Public License v3.0. See the [`LICENSE`](LICENSE) file for details.

## Copyright

Copyright (c) 2023, Intelligent Systems Lab, University of Rome Tor Vergata
