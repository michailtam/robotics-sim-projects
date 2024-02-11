# If not working, first do: sudo rm -rf /tmp/.docker.xauth
# It still not working, try running the script as root.
# Build the image first
# docker build -t <distro>_gpu .
# then run this script
# xhost local:root


XAUTH=/tmp/.docker.xauth

docker run -it \
    --name=ros2_<distro>_gpu \
    --user vmike \
    --env="DISPLAY=$DISPLAY" \
    --env="QT_X11_NO_MITSHM=1" \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    --env="XAUTHORITY=$XAUTH" \
    --runtime=nvidia \
    --gpus all \
    --volume="$XAUTH:$XAUTH" \
    --network=host \
    --privileged \
    --volume /media/mikelap/DATA1/GitRepos/robotics:/home/devel \
    <distro>_gpu \
    bash

echo "Done."