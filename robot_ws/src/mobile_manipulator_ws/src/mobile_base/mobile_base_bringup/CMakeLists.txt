cmake_minimum_required(VERSION 3.5)
project(mobile_base_bringup)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED) 
find_package(rclpy REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(xacro REQUIRED)
find_package(urdf REQUIRED)
find_package(mobile_base_description REQUIRED)

## CPP EXECUTABLES
include_directories(include)

## Create the cpp executables
add_executable(cpp_exe src/cpp_node.cpp)
ament_target_dependencies(cpp_exe rclcpp)

# Install the cpp executables
install(TARGETS
  cpp_exe
  DESTINATION lib/${PROJECT_NAME}
)

## PYTHON EXECUTABLES
# Create Python modules
ament_python_install_package(${PROJECT_NAME})

## Install Python executables
install(PROGRAMS
  scripts/py_node.py
  DESTINATION lib/${PROJECT_NAME}
)

## Install other required directories
install(
  DIRECTORY config launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
