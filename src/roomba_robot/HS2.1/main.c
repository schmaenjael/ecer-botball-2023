#include <stdbool.h>
#include "kipr/wombat.h"

void moveservo(int port, int position) {
    enable_servos();
    set_servo_position(port, position);
    msleep(1000);
}

void movemotor(int port, int position, int motorpower, int limitswitchport) {
    clear_motor_position_counter(port);
    if (digital(limitswitchport) == 0) {
        while (get_motor_position_counter(port) <= position) {
            motor(port, motorpower);
            msleep(10);
        }
    }
}

void setupsensordata() {
    set_create_distance(0);
    set_create_total_angle(0);
}


void printsensordata() {
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

bool setupcamera() {
    if (camera_open() == 0 || camera_update() == 0) return false;
    return true;
}

void setuprobot(bool debug, bool camera) {
    create_connect();
    setupsensordata();
    if (debug == true) {
        printsensordata();
    }
    if (camera) {
        if (setupcamera()) printf("%s", "Camera initialized");
        else printf("%s", "Camera Error");
    }
    enable_servos();
}

void shutdownrobot(bool camera) {
    if (camera) {
        camera_close();
    }
    disable_servos();
    ao();
    create_stop();
    create_disconnect();
}

void drivestraight(int speed, bool direction, int distance,
                   bool watch_for_touch) { //false backwards true forwards distance in mm
    if (direction == true) {
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
    // deg - nach rechts + nach links
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
    bool exit;
    exit = true;
    int speed = 100;
    while (exit) {
        char input;
        printf("%s", "Please provide input:\n");
        scanf("%c", &input);
        if (input == 'w') {
            drivestraight(speed, true, 25, true);
        }
        if (input == 's') {
            drivestraight(speed, false, 25, true);
        }
        if (input == 'd') {
            turn(speed / 2, -45);
        }
        if (input == 'a') {
            turn(speed / 2, 45);
        }
        if (input == 'x') {
            exit = false;
        }
        if (input == 'm') {
            printf("%s", "Please provide speed:\n");
            scanf("%d", &speed);
        }
    }
}

void movey(int servoport, int coord) {
    moveservo(servoport, coord);
}

void openclaw(int servoport) {
    moveservo(servoport, 2047);
}


void closeclaw(int servoport) {
    moveservo(servoport, 0);
}


void getObject(int channel){
    if(!get_object_count(channel)) return;
    camera_update();

    get_object_center_x(channel, 0);
    get_object_center_y(channel, 0);
}

void movexarm(int port, int position, int limitswitchport) {
    movemotor(port, position, 100, limitswitchport);
}

void levelarm(int port, int position, int motorpower, int limitswitchport) {
    clear_motor_position_counter(port);
    while (digital(limitswitchport) == 0) {
        motor(port, motorpower);
        msleep(10);
    }
    printf("%s", get_motor_position_counter(port));
}

int main() {
    setuprobot(false, false);
    wasd();
    turn(100, 90);
    shutdownrobot(false);
    return 0;
}
