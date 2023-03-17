#include <kipr/wombat.h>


//Only God knows why this Code does work!



void calibration(){
    //normal Positions
    int servoArm = 1900;
    int servoTurnArm = 1500;
    int servoHand = 100;
    int motorArm = 12000;
    
    
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
    
    while(get_motor_position_counter(0)<=5500){
        motor(0, 100);
        msleep(1);
    }
    motor(0,0);
    set_servo_position(2,550);
}



void drive_left_of_line(){
    
    while(!get_create_lbump() || !get_create_rbump()){
        create_drive_direct(100,50);
        if(get_create_rfcliff_amt()<=2000){
            create_drive_direct(0,100);
            msleep(100);
        }
    }
    create_drive_direct(0,0);
    
}



int main()
{
    enable_servos();
    create_connect();
    
    printf("left: %i\nright: %i\n", get_create_lfcliff_amt(), get_create_rfcliff_amt());
    
    calibration();
    msleep(1);
    
    set_servo_position(0,1500);
    
    drive_left_of_line();							//driving on black line until hitting wall to find right position
    
    create_drive_direct(-500,-500);					//-------------------------------------------------------------------
    msleep(1500);
    create_drive_direct(100,-100);    				//driving back and turning in direction of ring
    msleep(820);
    create_drive_direct(0,0);
    clear_motor_position_counter(0);				//-------------------------------------------------------------------
    
    grappling_position();							//arm goes in right position to pefectly grab the ring
    
    create_drive_direct(200,200);					//
    msleep(2100);									//driving to the ring
    create_drive_direct(0,0);						//
    
    set_servo_position(2,100);						//grab ring
    msleep(200);
    
    create_drive_direct(-100,-100);
  	msleep(700);
    create_drive_direct(0,0);
    set_servo_position(1,0);
    msleep(100);
    
    
    while(get_motor_position_counter(0)>=3000){
        motor(0, -100);
        msleep(1);
    }
    motor(0,0);
    
    create_drive_direct(-100,-100);
    msleep(300);
    create_drive_direct(0,0);
    
    while(get_motor_position_counter(0)>=1000){
        motor(0, -100);
        msleep(1);
    }
    motor(0,0);
    
    
    create_drive_direct(-100,100);
  	msleep(300);
    create_drive_direct(-100,-100);
    msleep(300);
    create_drive_direct(0,0);
    set_servo_position(1,600);
  	msleep(300);
    
    while(get_motor_position_counter(0)>=0){
        motor(0, -2000);
        msleep(1);
    }
    
    
    
    //turn_arm_back();

    printf("Button pushed: %i\n", get_motor_position_counter(0));
    return 0;
}