#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

struct Velocities {
    float linear_x;
    float angular_z;
};

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // Request a service and pass the velocities to drive the robot towards the ball
    if(lin_x == 0.0 and ang_z == 0.0)
        ROS_INFO_STREAM("The robot has stopped!!!");
    else
        ROS_INFO_STREAM("The robots velocities are linear_x: " << std::to_string(lin_x) << ", angle_z: " << std::to_string(ang_z));
    
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    // Call the safe_move service and pass the requested joint angles
    if (!client.call(srv))
        ROS_ERROR("Failed to call service safe_move");
}

// Determines the ball orientation related to the view of the robot (left, forward, right)
Velocities determine_ball_position(int pos, int width) 
{
    // Calculates the intervalls of the left, forward and right area
    int interval = width / 3;
    int left_interval = interval;
    int forward_interval = interval + interval;

    int index = pos % width;  // Transforms the 1d-value into a 2d-value
    Velocities vel;

    // The ball is on the left side of the robots view
    if( (index >= 0) && (index <= left_interval) ) {
        vel.linear_x = 0.25;
        vel.angular_z = 1.57;
    }
    // Else the ball is in front of the robot
    else if( (index >= left_interval) && (index <= forward_interval) ) {
        vel.linear_x = 0.25;
        vel.angular_z = 0.0;
    }
    // Else the ball is on the right side of the robots view
    else if( (index >= forward_interval) && (index <= width) ) {
        vel.linear_x = 0.25;
        vel.angular_z = -1.57;
    }
    return vel; // Return the velocities
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
    int white_pixel = 255;

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
    int image_size = img.step * img.height;
    int index = -1;
    
    for(int i=0; i<image_size; i=i+2) {
        // Checks if the ball is white (i.e. R=255, G=255, B=255)
        if(img.data[i] == white_pixel and img.data[i+1] == white_pixel and img.data[i+2] == white_pixel) {
            index = i;
            break;
        }
    }

    // If the index is != 0, then the robot sees the ball
    if(index != 0) {
        Velocities vel = determine_ball_position(index, img.step);   // Calculates the column number of the index
        drive_robot(vel.linear_x, vel.angular_z);
    } else {
        // TODO: Calls the service to Stops the robot
        drive_robot(0.0, 0.0);
    }
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
