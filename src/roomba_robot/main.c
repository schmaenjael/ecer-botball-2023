#include <kipr/wombat.h>

/* Defining Boolean values */
#define false 0
#define true 1
#define boolean int

/* Pre-defining functions */
void grappling_position();
void turn_arm_back();
void calibration();
void turn_arm();

/*
    -> Since KIPR provides functions using snake_case, I'd recommend also switching to snake_case for our functions and variables
    -> Use boolean as return type for TRUE/FALSE values from now on!
*/

int main()
{
    calibration();
    msleep(1);

    enable_servos();
    create_connect();

    clear_motor_position_counter(0);

    grappling_position();

    set_servo_position(2, 100);
    msleep(100);
    create_drive_direct(-1, -1);

    set_servo_position(1, 0);
    msleep(100);

    while (get_motor_position_counter(0) >= 2000)
    {
        motor(0, -100);
        msleep(1);
    }

    msleep(500);

    // turn_arm_back();

    printf("Button pushed: %i\n", get_motor_position_counter(0));
    return 0;
}

void calibration()
{
    // normal positions
    int servo_arm = 2000;
    int servo_turn_arm = 1500;
    int servo_hand = 1500;
    int motor_arm = 8900;

    enable_servos();
    msleep(5);
    set_servo_position(0, servo_arm);
    msleep(5);
    set_servo_position(1, servo_turn_arm);
    msleep(5);
    set_servo_position(2, servo_hand);
    msleep(5);
    disable_servos();

    while (!digital(0))
    {
        motor(0, -100);
        msleep(1);
    }
    clear_motor_position_counter(0);

    while (get_motor_position_counter(0) <= motor_arm)
    {
        motor(0, 100);
        msleep(1);
    }
    motor(0, 0);
}

void turn_arm()
{
    set_servo_position(1, 400);
    msleep(500);
}

void turn_arm_back()
{
    set_servo_position(1, 1500);
    msleep(500);
}

void grappling_position()
{
    set_servo_position(0, 1000);
    turn_arm();

    while (get_motor_position_counter(0) <= 5000)
    {
        motor(0, 100);
        msleep(1);
    }

    msleep(10);
}
