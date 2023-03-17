#include <kipr/wombat.h>


void calibration(){
    //default positions
    int servoArm = 2000;
    int servoTurnArm = 1500;
    int servoHand = 100;
    int motorArm = 12700;


    while(!digital(0)){
        motor(0, -100);
        msleep(1);
    }
    clear_motor_position_counter(0);


    msleep(5);
    set_servo_position(0,servoArm);
    msleep(5);
    set_servo_position(1,servoTurnArm);
    msleep(5);
    set_servo_position(2,servoHand);
    msleep(500);

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

    while(get_motor_position_counter(0)<=6500){
        motor(0, 100);
        msleep(1);
    }
    motor(0,0);
    set_servo_position(2,650);
}

void drive_left_of_line(){

    while(!get_create_lbump() || !get_create_rbump()){
        create_drive_direct(100,50);
        if(get_create_rfcliff_amt()<=2000){
            create_drive_direct(0,100);
            msleep(200);
        }
    }
}



int main()
{
    enable_servos();
    create_connect();

    printf("left: %i\nright: %i\n", get_create_lfcliff_amt(), get_create_rfcliff_amt());

    calibration();
    msleep(1);

    set_servo_position(0,1500);

    drive_left_of_line();

    create_drive_direct(-500,-500);
    msleep(1500);
    create_drive_direct(100,-100);
    msleep(900);
    create_drive_direct(0,0);
    clear_motor_position_counter(0);

    grappling_position();
    create_drive_direct(200,200);
    msleep(2100);
    create_drive_direct(0,0);
    set_servo_position(2,100);
    msleep(200);
    create_drive_direct(-100,-100);
    msleep(700);
    create_drive_direct(0,0);
    set_servo_position(1,0);
    msleep(100);

    while(get_motor_position_counter(0)>=2000){
        motor(0, -100);
        msleep(1);
    }
    create_drive_direct(-100,100);
    msleep(300);
    create_drive_direct(0,0);
    set_servo_position(1,600);
    msleep(300);
    while(get_motor_position_counter(0)>=0){
        motor(0, -100);
        msleep(1);
    }

    printf("Button pushed: %i\n", get_motor_position_counter(0));
    return 0;
}