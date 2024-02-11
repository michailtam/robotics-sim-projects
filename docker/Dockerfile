FROM osrf/ros:${ROS_DISTRO}-desktop-full

RUN apt-get update \
    && apt-get install -y \
    nano \
    vim \
    gedit \
    git \ 
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

# Creates a non-root user.
ARG USERNAME=vmike
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Adds a new user named vmike.
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && mkdir /home/$USERNAME/.config && chown $USER_UID:$USER_GID /home/$USERNAME/.config

# Adds Nvidia-GPU support.
ENV NVIDIA_VISIBLE_DEVICES \
    ${NVIDIA_VISIBLE_DEVICES:-all}
ENV NVIDIA_DRIVER_CAPABILITIES \
    ${NVIDIA_DRIVER_CAPABILITIES:+$NVIDIA_DRIVER_CAPABILITIES,}graphics

# Sets up the sudo command.
RUN apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME\
    && chmod 0440 /etc/sudoers.d/$USERNAME \
    && rm -rf /var/lib/apt/lists/*

# Install packages for ROS and Gazebo.
RUN apt-get update \
    && pip install colcon-argcomplete \
    colcon-cd

# Installs Gazebo and additional packages.
RUN apt-get install -y gazebo \
    && apt-get install -y ros-${ROS_DISTRO}-gazebo-plugins \
    ros-${ROS_DISTRO}-gazebo-ros \
    ros-${ROS_DISTRO}-gazebo-ros-pkgs \
    ros-${ROS_DISTRO}-gazebo-ros2-control

RUN apt-get install -y python3-colcon-common-extensions \
    && apt-get install -y ros-${ROS_DISTRO}-joint-state-publisher \
    ros-${ROS_DISTRO}-joint-state-publisher-gui \
    ros-${ROS_DISTRO}-xacro

RUN apt-get install -y ros-${ROS_DISTRO}-ros2-control \
    && apt-get install -y ros-${ROS_DISTRO}-ros2-controllers \
    ros-${ROS_DISTRO}-controller-manager

# Creates the workspace and changes into it.
RUN mkdir ~/devel
WORKDIR /home/devel

# Sets the environment variables.
ENV LANG=en_US.UTF-8
ENV DISPLAY=:1

COPY bashrc /home/${USERNAME}/.bashrc 

RUN echo "Image created!"
