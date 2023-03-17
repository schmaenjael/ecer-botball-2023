#include <stdbool.h>
#include "kipr/wombat.h"
#include "tasks/stair_task/stair_task.c"

int main(){
    setuprobot(false, false);
    calibration();
    drive_to_botgal();
    shutdownrobot(false);
}