#include <kipr/wombat.h>
void drive(int motorA, int motorB,int time){
    motor(0,motorA);
    motor(1,motorB);
    msleep(time);
}

void driveStraightOnBlackLine(int motorA, int motorB){
    if(analog(1) <300 && analog(2) <300){
        drive(motorA,motorB,10);
    }else if(analog(1) >300 && analog(2) >300){
        drive(motorA,motorB,10);	    
    }else if(analog(1)>300){
        drive(motorA,0,10);
    }else if(analog(2)>300){
        drive(0,motorB,10);
    }
}
int noCollisionFrontSide(){
    if(digital(0) == 1||digital(1) == 1){
        return 0;
    }else{
        return 1;
    }
}
void driveToStartPoint(){
    enable_servo(0);
    msleep(10);
    if(get_servo_enabled(0)){
        set_servo_position(0,300);
    }
    drive(70,8,2250);
    drive(70,70,4000);
    drive(-90,-10,1300);
    drive(70,70,1100);
    set_servo_position(0,60);
    drive(-70,-2,300);
    drive(-70,-50,800);
    drive(-70,-60,500);
    set_servo_position(0,1400);
    drive(20,70,900);
}
int main()
{
    wait_for_light(0);//the argument is the analog port that you are using to detect the light change
    //THERE SHOULD BE NO COMMANDS BETWEEN HERE UNLESS YOU REALLY KNOW WHAT YOU ARE DOING AND HAVE A REASON TO
    shut_down_in(117);//the argument you pass here is how many seconds you want the robot to shut down in
    driveToStartPoint();
    while(noCollisionFrontSide()){
    	driveStraightOnBlackLine(60,60);
    }
    return 0;
}

