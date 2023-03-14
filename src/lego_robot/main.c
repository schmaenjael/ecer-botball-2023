#include <kipr/wombat.h>

/* Defining Boolean values */
#define false 0
#define true 1
#define boolean int

/*
    -> Since KIPR provides functions using snake_case, I'd recommend also switching to snake_case for our functions and variables
    -> Use boolean as return type for TRUE/FALSE values from now on!
*/

void follow_black_line(int, int);
void drive(int, int, int);
void drive_to_start();
boolean is_frontal_collision();
boolean drive_distance(int);

int main()
{
    drive_to_start();
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);

    return 0;
}

void drive(int motor_a, int motor_b, int time)
{
    motor(0, motor_a);
    motor(1, motor_b);
    msleep(time);
}

boolean drive_distance(int distance)
{
    if (get_motor_position_counter(0) < distance)
        return true;

    motor(0, 0);
    motor(1, 0);
    set_servo_position(0, 30);
    msleep(20);

    return false;
}

boolean is_frontal_collision()
{
    if (digital(0) == 1 || digital(1) == 1)
        return false;
    else
        return true;
}

void follow_black_line(int motor_a, int motor_b)
{
    if (analog(1) < 500 && analog(2) < 500)
        drive(motor_a, motor_b, 30);
    else if (analog(1) > 500 && analog(2) > 500)
        drive(motor_a, motor_b, 10);
    else if (analog(1) > 500)
        drive(motor_a, 0, 10);
    else if (analog(2) > 500)
        drive(0, motor_b, 10);
}

void drive_to_start()
{
    enable_servo(0);
    msleep(30);
    set_servo_position(0, 1000);
    msleep(10);

    drive(80, 70, 1100);
    drive(60, -60, 550);
    drive(100, 100, 600);
    drive(85, 72, 2850);
    drive(0, 0, 10);
    set_servo_position(0, 0);
    msleep(500);
    drive(-100, 100, 1600);
    set_servo_position(0, 1000);

    while (drive_distance(125000) && is_frontal_collision())
    {
        follow_black_line(60, 60);
    }
}
