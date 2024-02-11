# Docker for ROS2 and UI support

## Content
This branch contains **Docker** related files for the usage with ROS2, Gazebo and RViz.

## Notes

### Nvidia GPU support for Docker 

#### Tested on
<ul>
    <li>Acer V15 Nitro laptop (bought in 2017)</li>
    <li>Ubuntu 22.04 LTS</li>
    <li>GeForce GTX 860M with 2GB RAM</li>
    <li>8GB RAM</li>
</ul>

#### Installation steps
1. [How to Use an NVIDIA GPU with Docker Containers](https://www.howtogeek.com/devops/how-to-use-an-nvidia-gpu-with-docker-containers/)
2. [How to install CUDA 9.1](https://gist.github.com/DaneGardner/accd6fd330348543167719002a661bd5)
3. [How to install the Nvidia Container Toolkit](https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/latest/install-guide.html)
4. [Documentation for the Toolkit](https://github.com/NVIDIA/nvidia-container-toolkit)
5. Build the container with GPU support using the **Dockerfile**: ```$ docker build -t <container_name> .```
6. Run the **shell script**: ```$ ./run_docker_gpu.bash```