# ROS2 Workspaces

## Content
This folder contains **ROS2** workspaces for robotics applications implemented in **C++** and **Python**.

## Notes

### Setup a custom GAZEBO MODEL PATH
The main reason to setup a custom model path is, that **Gazebo starts quicker** and you do not need to contain all the models in the **models folder** for every project, which consumes unnecessary space. That's, why it is recommended to setup this path only once in the **bashrc file**. Nevertheless, it's good habit to add a models folder to each of your project (don't forget to add the entry in the CMakeLists.txt file), if you want to use only specific ones. But, be careful not to overfill the space. The following steps describe how you can setup the models path in the bashrc file and how to chek it subsequently:

```bash
1. Issue in the terminal $ sudo gedit ~/.bashrc
2. And then append the following lines at the end of the bashrc file (keep in mind to set the paths according to your system and ROS distro).

...

## ROS2
source /opt/ros/humble/setup.bash
source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash

## Activating ROS Venvs
source /media/mikelap/DATA1/Development/python/virtualenvs/robotics/bin/activate

## Sourcing
source /usr/share/colcon_cd/function/colcon_cd.sh
source /media/mikelap/DATA1/GitRepos/robotics/robot_ws/install/setup.bash

## Change to Project Paths
cd /media/mikelap/DATA1/GitRepos/robotics/robot_ws

## Sets the default paths for Gazebo
export GAZEBO_MODEL_PATH=/usr/share/gazebo-11/models:$GAZEBO_MODEL_PATH
export GAZEBO_PLUGIN_PATH=/usr/lib/x86_64-linux-gnu/gazebo-11/plugins:$GAZEBO_PLUGIN_PATH

3. In the terminal issue $ echo $GAZEBO_MODEL_PATH to check the path.
output: $ /usr/share/gazebo-11/models:
```

### Show Gazebo where to find the robots mesh files
If your robot consists of any mesh files for example was created by using a CAD software like [Fusion360](https://www.autodesk.com/products/fusion-360/overview?term=1-YEAR&tab=subscription), then the file extension of the meshes will be either of type **.STL** or **.DAE** (both of them are recommended). Therefore, **Gazebo** will not be able to find them, if you do not explicitly specify the path. This can be done by modifying the **package.xml** file by inserting the following snipped before the **package** ending tag:
```xml
...
<export>
    <build_type>ament_cmake</build_type>
    <!-- The following is necessary, so Gazebo is able to find the models mesh files. You have to specify the absolute path to the shared robot_description folder.-->
    <gazebo_ros gazebo_model_path="/media/mikelap/DATA1/GitRepos/robotics/robot_ws/install/ bcn3d_moveo_description/share"/>
</export>
...
```