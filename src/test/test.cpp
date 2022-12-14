#include <ros/ros.h>
#include "wheel_planner/wheel_planner.hpp"
#include "conio.h"
int main(int argc, char **argv)
{
    ros::init(argc, argv, "test");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<wheel_tokyo_weili::wheel_planner>("/wheel/planner", 1);
    ros::Rate loop_rate(10);
    wheel_tokyo_weili::wheel_planner msg;

    char kbin;
    while (kbin != 27)
    {
        // Get keyboard input
        if (kbhit())
        {
            kbin = getch();
            // Find speeds
            switch (toupper(kbin))
            {
            case 'W':
                msg.distance_x = 30;
                msg.distance_y = 0;
                msg.distance_z = 0;
                break;
            case 'D':
                msg.distance_y = 30;
                msg.distance_x = 0;
                msg.distance_z = 0;
                break;
            case 'S':
                msg.distance_x = -30;
                msg.distance_y = 0;
                msg.distance_z = 0;
                break;
            case 'A':
                msg.distance_y = -30;
                msg.distance_x = 0;
                msg.distance_z = 0;
                break;
            case 'Q':
                msg.distance_z = -90;
                msg.distance_y = 0;
                msg.distance_x = 0;
                break;
            case 'E':
                msg.distance_z = 90;
                msg.distance_y = 0;
                msg.distance_x = 0;
                break;
            case 'O':
                msg.far_left = true;
                msg.far_right = false;
                break;
            case 'P':
                msg.far_left = false;
                msg.far_right = true;
                break;
            case 'R':
                msg.encoder_reset = true;
                msg.distance_x = 0;
                msg.distance_y = 0;
                msg.distance_z = 0;
                break;
            default:
                msg.distance_x = 0;
                msg.distance_y = 0;
                msg.distance_z = 0;
                break;
            }
            pub.publish(msg);
            loop_rate.sleep();
            msg.far_left = false;
            msg.far_right = false;
            msg.far_right = false;
        }
    }
    return 0;
}
