#include <stdbool.h>
#include "kipr/wombat.h"
#define DEBUG true

void move_servo(int port, int position) {
    enable_servos();
    set_servo_position(port, position);
    msleep(1000);
}

void move_motor(int port, int position, int motorpower, int limitswitchport) {
    clear_motor_position_counter(port);
    if (digital(limitswitchport) != 0) return;

    while (get_motor_position_counter(port) <= position) {
        motor(port, motorpower);
        msleep(10);
    }
}

void setup_sensordata() {
    set_create_distance(0);
    set_create_total_angle(0);
}


void print_sensordata() {
    printf("%d,%d,%s", get_create_rwdrop(), 0, "right wheel drop \n");
    printf("%d,%d,%s", get_create_rcliff(), 0, "right cliff \n");
    printf("%d,%d,%s", get_create_rlightbump(), 0, "right light bumper \n");
    printf("%d,%d,%s", get_create_rbump(), 0, "right bumper \n");
    printf("%d,%d,%s", get_create_rflightbump(), 0, "right light front bumper \n");
    printf("%d,%d,%s", get_create_rfcliff(), 0, "right cliff \n");
    printf("%d,%d,%s", get_create_rclightbump(), 0, "right cliff light bumper \n");
    printf("%d,%d,%s", get_create_cwdrop(), 0, "front drop wheel \n");
    printf("%d,%d,%s", get_create_lclightbump(), 0, "left cliff light bumper \n");
    printf("%d,%d,%s", get_create_lfcliff(), 0, "left front cliff \n");
    printf("%d,%d,%s", get_create_lflightbump(), 0, "left light bumper \n");
    printf("%d,%d,%s", get_create_lbump(), 0, "left bumper \n");
    printf("%d,%d,%s", get_create_llightbump(), 0, "left light bumper \n");
    printf("%d,%d,%s", get_create_lcliff(), 0, "left cliff \n");
    printf("%d,%d,%s", get_create_lwdrop(), 0, "left wheel drop \n");
    printf("%d,%d,%s", get_create_distance(), 0, "total distance\n");
    printf("%d,%d,%s", get_create_total_angle(), 0, "total angle \n");
}

bool setup_camera() {
    if (camera_open() == 0 || camera_update() == 0) return false;
    return true;
}

void setup_robot(bool debug, bool camera) {
    create_connect();
    setup_sensordata();
#ifdef DEBUG
    print_sensordata();
#endif
    if (camera) {
        if (setup_camera()) printf("%s", "Camera initialized");
        else printf("%s", "Camera Error");
    }
    enable_servos();
}

void shutdown_robot(bool camera) {
    if (camera) {
        camera_close();
    }
    disable_servos();
    ao();
    create_stop();
    create_disconnect();
}

void drive_straight(int speed, enum direction{forward,backward}; direction, int distance,bool watch_for_touch) { // distance in mm
    if (direction == forward) {
        set_create_distance(0);
        while (get_create_distance() <= (distance)) {
            create_drive_direct(speed, speed);
            if (watch_for_touch) {
                if (get_create_lbump() || get_create_rbump() == true) {
                    set_create_distance(distance);
                }
            }
        }
    } else {
        set_create_distance(0);
        while ((-1 * get_create_distance()) <= (distance)) {
            create_drive_direct(speed * -1, speed * -1);
        }
    }
}

void turn(int speed, int deg) {
    // deg - turn to right  + turn to left
    set_create_distance(0);
    set_create_total_angle(0);
    if (deg > 0) {
        while (get_create_total_angle() <= deg) {
            create_drive_direct(speed * -1, speed);
        }
    } else {
        while (get_create_total_angle() >= deg) {
            create_drive_direct(speed, speed * -1);
        }
    }
}

void wasd() { // function to control robot via webinterface
    bool exit = true;
    int speed = 100;
    while (exit) {
        char input;
        printf("%s", "Please provide input:\n");
        scanf("%c", &input);
        switch (input) {
            case 'w':
                drive_straight(speed, forward, 25, true);
                break;
            case 's':
                drive_straight(speed, backward, 25, true);
                break;
            case 'd':
                turn(speed / 2, -45);
                break;
            case 'a':
                turn(speed / 2, 45);
                break;
            case 'x':
                exit = false;
                break;
            case 'm':
                printf("%s", "Please provide speed:\n");
                scanf("%d", &speed);
                break;
            default:
                printf("%s", "Invalid input\n");
                break;
        }
    }
}

void calibration(){
    // default positions
    int servo_arm = 2000;
    int servoTurnArm = 1500;
    int servoHand = 100;
    int motorArm = 12700;


    while(!digital(0)){
        motor(0, -100);
        msleep(1);
    }
    clear_motor_position_counter(0);
    msleep(5);
    set_servo_position(0,servo_arm);
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

void grab_botgal(){
    clear_motor_position_counter(0);
    while(get_motor_position_counter(0) <= 800){
        motor(0, -100);
        msleep(1);
    }
    set_servo_position(1,1400)
    set_servo_position(0,)
}

void drive_to_botgal(){
    drive_straight(100,backward,10,false);
    turn(100,-90);
    drive_straight(100,forward,800,false);
    turn(100,45);
    drive_straight(100,forward,400,false);
    turn(100,55);
    drive_straight(100,forward,430,false);
}
}