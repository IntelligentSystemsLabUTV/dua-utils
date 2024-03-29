cmake_minimum_required(VERSION 3.8)
project(dynamic_systems)

set(CMAKE_BUILD_TYPE "RelWithDebInfo")

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -fvisibility=hidden)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(Eigen3 3.4 REQUIRED NO_MODULE)
find_package(polynomial_kit REQUIRED)

# Dynamic systems base library configuration
add_library(dynamic_systems SHARED
  src/dynamic_systems/base/system.cpp
  src/dynamic_systems/control/integrator.cpp
  src/dynamic_systems/control/lti.cpp
  src/dynamic_systems/control/pid.cpp
  src/dynamic_systems/control/utils.cpp
  src/dynamic_systems/filters/jump_filter.cpp)
target_compile_features(dynamic_systems PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_compile_definitions(dynamic_systems PRIVATE "DYNAMIC_SYSTEMS_BUILDING_LIBRARY")
target_include_directories(dynamic_systems PUBLIC
  ${EIGEN3_INCLUDE_DIR}
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_link_libraries(dynamic_systems
  Eigen3::Eigen)

ament_target_dependencies(dynamic_systems
  polynomial_kit)

# Libraries installation
install(
  DIRECTORY include/
  DESTINATION include)
install(
  TARGETS dynamic_systems
  EXPORT dynamic_systemsTargets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# Export all dependencies and library targets for this package
ament_export_targets(dynamic_systemsTargets HAS_LIBRARY_TARGET)
ament_export_dependencies(
  polynomial_kit)

ament_package()
