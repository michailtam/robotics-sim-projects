# Install script for directory: /media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/src/mobile_base/mobile_base_bringup

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/install/mobile_base_bringup")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/mobile_base_bringup/cpp_exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/mobile_base_bringup/cpp_exe")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/mobile_base_bringup/cpp_exe"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/mobile_base_bringup" TYPE EXECUTABLE FILES "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/build/mobile_base_bringup/cpp_exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/mobile_base_bringup/cpp_exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/mobile_base_bringup/cpp_exe")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/mobile_base_bringup/cpp_exe"
         OLD_RPATH "/opt/ros/humble/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/mobile_base_bringup/cpp_exe")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mobile_base_bringup/environment" TYPE FILE FILES "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/build/mobile_base_bringup/ament_cmake_environment_hooks/pythonpath.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mobile_base_bringup/environment" TYPE FILE FILES "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/build/mobile_base_bringup/ament_cmake_environment_hooks/pythonpath.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3.10/site-packages/mobile_base_bringup-0.0.0-py3.10.egg-info" TYPE DIRECTORY FILES "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/build/mobile_base_bringup/ament_cmake_python/mobile_base_bringup/mobile_base_bringup.egg-info/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3.10/site-packages/mobile_base_bringup" TYPE DIRECTORY FILES "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/src/mobile_base/mobile_base_bringup/mobile_base_bringup/" REGEX "/[^/]*\\.pyc$" EXCLUDE REGEX "/\\_\\_pycache\\_\\_$" EXCLUDE)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(
        COMMAND
        "/media/mikelap/DATA/Development/python/virtualenvs/robotics/bin/python3.10" "-m" "compileall"
        "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/install/mobile_base_bringup/lib/python3.10/site-packages/mobile_base_bringup"
      )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/mobile_base_bringup" TYPE PROGRAM FILES "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/src/mobile_base/mobile_base_bringup/scripts/py_node.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mobile_base_bringup/" TYPE DIRECTORY FILES
    "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/src/mobile_base/mobile_base_bringup/config"
    "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/src/mobile_base/mobile_base_bringup/launch"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/package_run_dependencies" TYPE FILE FILES "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/build/mobile_base_bringup/ament_cmake_index/share/ament_index/resource_index/package_run_dependencies/mobile_base_bringup")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/parent_prefix_path" TYPE FILE FILES "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/build/mobile_base_bringup/ament_cmake_index/share/ament_index/resource_index/parent_prefix_path/mobile_base_bringup")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mobile_base_bringup/environment" TYPE FILE FILES "/opt/ros/humble/share/ament_cmake_core/cmake/environment_hooks/environment/ament_prefix_path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mobile_base_bringup/environment" TYPE FILE FILES "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/build/mobile_base_bringup/ament_cmake_environment_hooks/ament_prefix_path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mobile_base_bringup/environment" TYPE FILE FILES "/opt/ros/humble/share/ament_cmake_core/cmake/environment_hooks/environment/path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mobile_base_bringup/environment" TYPE FILE FILES "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/build/mobile_base_bringup/ament_cmake_environment_hooks/path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mobile_base_bringup" TYPE FILE FILES "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/build/mobile_base_bringup/ament_cmake_environment_hooks/local_setup.bash")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mobile_base_bringup" TYPE FILE FILES "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/build/mobile_base_bringup/ament_cmake_environment_hooks/local_setup.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mobile_base_bringup" TYPE FILE FILES "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/build/mobile_base_bringup/ament_cmake_environment_hooks/local_setup.zsh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mobile_base_bringup" TYPE FILE FILES "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/build/mobile_base_bringup/ament_cmake_environment_hooks/local_setup.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mobile_base_bringup" TYPE FILE FILES "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/build/mobile_base_bringup/ament_cmake_environment_hooks/package.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/packages" TYPE FILE FILES "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/build/mobile_base_bringup/ament_cmake_index/share/ament_index/resource_index/packages/mobile_base_bringup")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mobile_base_bringup/cmake" TYPE FILE FILES
    "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/build/mobile_base_bringup/ament_cmake_core/mobile_base_bringupConfig.cmake"
    "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/build/mobile_base_bringup/ament_cmake_core/mobile_base_bringupConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mobile_base_bringup" TYPE FILE FILES "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/src/mobile_base/mobile_base_bringup/package.xml")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/media/mikelap/DATA/GitRepos/robotics/robot_ws/src/mobile_manipulator_ws/build/mobile_base_bringup/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
