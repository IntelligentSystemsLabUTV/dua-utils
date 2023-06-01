# pose_kit

Collection of C++ libraries based on [`Eigen`](http://eigen.tuxfamily.org/index.php?title=Main_Page) for storing and operating on the state of a rigid body in 3D space, for fast and efficient computations.

## Contents

Three classes:

- `Pose`: position and orientation,
- `KinematicPose`: position, orientation and linear/angular velocity.
- `DynamicPose`: position, orientation, linear/angular velocity and linear/angular acceleration.

All classes can either hold and represent the **state** of a rigid body, or a **transformation** between two reference frames to apply to these objects. In the latter case, **types must coincide**, since the application of a transformation involves different operations depending on the type of the object to which it is applied.

### Features

All classes are based on the `double` type, and offer:

- Various constructors for different use cases and data availability.
- Representation of attitude as both Euler angles and quaternions.
- Full compatibility with fixed-size Eigen geometric types.
- Getters and setters.
- Assigment operators, copy and move constructors.
- Compatibility with ROS 2 messages from the [`dua_interfaces`](https://github.com/IntelligentSystemsLabUTV/dua-utils/blob/master/src/dua_interfaces/README.md) package.
- Compatibility with ROS 2 messages from standard packages and the `tf2` library.
- Integration with the `ament` build system.

### Geometric operations

Currently implemented and planned:

- [x] Right-multiplication in homogeneous coordinates (as `operator*`).
- [x] Application of ROS `tf` transforms as right-multiplication in homogeneous coordinates.

## Requirements

Builds on ROS 2 Humble Hawksbill with Eigen 3.4.0 or higher.

See [`package.xml`](package.xml) for more information.

---

## License

This work is licensed under the GNU General Public License v3.0. See the [`LICENSE`](LICENSE) file for details.

## Copyright

Copyright (c) 2023, Intelligent Systems Lab, University of Rome Tor Vergata