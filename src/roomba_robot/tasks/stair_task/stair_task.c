#include <kipr/wombat.h>


//Only God knows why this Code does work!



void calibration(){
    //normal Positions
    int servo_arm = 1900;
    int servo_turn_arm = 1500;
    int servo_hand = 100;
    int motor_arm = 12000;
    
    
    while(!digital(0)){
        motor(0, -100);
        msleep(1);
    }
    clear_motor_position_counter(0);
    

    msleep(5);
    set_servo_position(0,servo_arm);
    msleep(5);
    set_servo_position(1,servo_turn_arm);
    msleep(5);
    set_servo_position(2,servo_hand);
    msleep(500);
    
    
    
    
    
    while(get_motor_position_counter(0)<=motor_arm){
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
    
    calibration();
    msleep(1);
    
    set_servo_position(0,1500);
    
    drive_left_of_line();				//driving on black line until hitting wall to find right position
    
    create_drive_direct(-500,-500);		//-------------------------------------------------------------------
    msleep(1500);
    create_drive_direct(100,-100);    	//driving back and turning in direction of ring
    msleep(820);
    create_drive_direct(0,0);
    clear_motor_position_counter(0);	//-------------------------------------------------------------------
    
    grappling_position();				//arm goes in right position to pefectly grab the ring
    
    create_drive_direct(200,200);		//
    msleep(2100);						//driving to the ring
    create_drive_direct(0,0);			//
    
    set_servo_position(2,100);			//grab ring
    msleep(200);
    
    create_drive_direct(-100,-100);		//
  	msleep(700);						//driving back, that arm would not hit the vertikal stair
    create_drive_direct(0,0);			//
    
    set_servo_position(1,0);			//tilt ring to the left that he can get moved
    msleep(100);						//to the left on the first stair
    
    while(get_motor_position_counter(0)>=3000){		//-----------------------------------------------
        motor(0, -100);
        msleep(1);									//move arm up
    }
    motor(0,0);										//-----------------------------------------------
    
    create_drive_direct(-100,-100);					//
    msleep(300);									//driving back, that arm would not hit the horizontal stair
    create_drive_direct(0,0);						//
    
    while(get_motor_position_counter(0)>=1000){		//-----------------------------------------------
        motor(0, -100);							
        msleep(1);									//move arm up to the height of the first stair
    }
    motor(0,0);										//-----------------------------------------------
    
    
    create_drive_direct(-100,100);		//-----------------------------------------------
  	msleep(300);
    create_drive_direct(-100,-100);		//drive to the left to get in position for the next stair 
    msleep(200);
    create_drive_direct(0,0);			//-----------------------------------------------
    
    set_servo_position(1,600);			//turn ring vertikal to go up the horizontal stair
  	msleep(300);
    
    while(get_motor_position_counter(0)>=-1500){		//-----------------------------------------------
        motor(0, -100);
        msleep(1);										//move arm up
    }
    motor(0,0);											//-----------------------------------------------
    
    set_servo_position(1,0);			//tilt ring to the left that he can get moved to the left on the second stair
														
    
    create_drive_direct(-100,-100);		//
    msleep(200);						//driving back, that arm would not hit the horizontal stair
    create_drive_direct(0,0);			//
    
    while(get_motor_position_counter(0)>=-3500){		//-----------------------------------------------
        motor(0, -100);
        msleep(1);										//move arm up to the height of the second stair
    }
    motor(0,0);											//-----------------------------------------------
    
    create_drive_direct(-100,50);						//
    msleep(400);										//drive to the left to get in position for the next stair
    create_drive_direct(0,0);							//
    
    
    //turn_arm_back();

    printf("Button pushed: %i\n", get_motor_position_counter(0));
    return 0;
}