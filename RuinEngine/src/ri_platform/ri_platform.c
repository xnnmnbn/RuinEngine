#include "ri_platform.h"

#include <stdio.h>

void ri__platform_init(RI_Platform *p) {
    ri_window_init();
    ri_input_init(p);
    ri_time_init(p);	
}

void ri__platform_kill(RI_Platform *p) {
    ri_input_kill(p);
    if (p->window.window != NULL) {
        ri_window_kill(p);
    }

    printf("Platform killed succesfully.\n");
}
