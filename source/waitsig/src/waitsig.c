#include "../include/waitsig.h"
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

bool is_waiting;

void HDL_SIG(int sig) {
    is_waiting = false;
}

void waitsig(int sig) {
    
    signal(sig, HDL_SIG);
    is_waiting = true;

    while(is_waiting) {
        pause();
    }
    
    signal(sig, SIG_DFL);
}
