#include <kipr/wombat.h>

void calibration(){
    //normal Positions
    int servoArm = 2000;
    int servoTurnArm = 1500;
    int servoHand = 1500;
    int motorArm = 8900;



    enable_servos();
    msleep(5);
    set_servo_position(0,servoArm);
    msleep(5);
    set_servo_position(1,servoTurnArm);
    msleep(5);
    set_servo_position(2,servoHand);
    msleep(5);
    disable_servos();

    while(!digital(0)){
        motor(0, -100);
        msleep(1);
    }
    clear_motor_position_counter(0);


    while(get_motor_position_counter(0)<=motorArm){
        motor(0, 100);
        msleep(1);
    }
    motor(0, 0);
}

void turn_arm(){
    set_servo_position(1,400);
    msleep(500);
}
void turn_arm_back(){
    set_servo_position(1,1500);
    msleep(500);
}


void grappling_position(){
    set_servo_position(0,1000);
    turn_arm();

    while(get_motor_position_counter(0)<=5000){
        motor(0, 100);
        msleep(1);
    }


    msleep(10);
}


int main()
{

    calibration();
    msleep(1);

    enable_servos();
    create_connect();

    clear_motor_position_counter(0);

    grappling_position();



    set_servo_position(2,100);
    msleep(100);
    create_drive_direct(-1,-1);

    set_servo_position(1,0);
    msleep(100);

    while(get_motor_position_counter(0)>=2000){
        motor(0, -100);
        msleep(1);
    }

    msleep(500);

    //turn_arm_back();

    printf("Button pushed: %i\n", get_motor_position_counter(0));
    return 0;
}