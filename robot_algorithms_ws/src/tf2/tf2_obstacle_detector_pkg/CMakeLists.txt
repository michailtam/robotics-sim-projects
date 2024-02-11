cmake_minimum_required(VERSION 3.5)
project(obstacle_detector_pkg)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(dependencies
  rclcpp
  tf2_ros
  geometry_msgs
  tf2_geometry_msgs
  sensor_msgs
  visualization_msgs
)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)

include_directories(include)

add_library(${PROJECT_NAME} SHARED
  src/obstacle_detector_pkg/obstacle_detector_node.cpp
  src/obstacle_detector_pkg/obstacle_monitor_node.cpp
)
ament_target_dependencies(${PROJECT_NAME} ${dependencies})

add_executable(obstacle_detector_main src/main_detector.cpp)
ament_target_dependencies(obstacle_detector_main ${dependencies})
target_link_libraries(obstacle_detector_main ${PROJECT_NAME})

install(TARGETS ${POJECT_NAME}
  obstacle_detector_main
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
