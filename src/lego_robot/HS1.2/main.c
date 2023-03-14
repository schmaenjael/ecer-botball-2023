#include <kipr/wombat.h>


void drive(int motorA, int motorB,int time){
    motor(0,motorA);
    motor(1,motorB);
    msleep(time);
}
int driveDistance(int distance){
    if(get_motor_position_counter(0) > distance){
        motor(0,0);
        motor(1,0);
        set_servo_position(0,30);
        msleep(20);
        return 0;
    }else{
        return 1;
    }
}
int noCollisionFrontSide(){
    if(digital(0) == 1||digital(1) == 1){
        return 0;
    }else{
        return 1;
    }
}

void driveStraightOnBlackLine(int motorA, int motorB){
    if(analog(1) <500 && analog(2) <500){
        drive(motorA,motorB,30);
    }else if(analog(1) >500 && analog(2) >500){
        drive(motorA,motorB,10);
    }else if(analog(1)>500){
        drive(motorA,0,10);
    }else if(analog(2)>500){
        drive(0,motorB,10);
    }

}

void driveToStartPoint(){
    enable_servo(0);
    msleep(10);
    set_servo_position(0,1000);
    msleep(10);
    
    drive(80,70,1100);
    drive(60,-60,550);
    drive(100,100,600);
    drive(85,72,2850);
    drive(0,0,10);
    set_servo_position(0,0);
    msleep(500);
    drive(-100,100,1600);
    set_servo_position(0,1000);
    while(driveDistance(125000)&&noCollisionFrontSide()){
        
    driveStraightOnBlackLine(60,60);
    }
}



int main(){

    driveToStartPoint();
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    
    return 0;
}

