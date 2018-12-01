#include "../include/waitsig.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define CODE_GO 0x1

bool pausing = true;
bool sendSIG = false;
pid_t child_pid;

void HDL_SIG(int sig) {
    kill(child_pid, SIGUSR1);
}

void HDL_SIGUSR1(int sig) {
    raise(SIGKILL);
}

void waitsig(int sig) {
    int _pipe_p[2], _pipe_c[2];
    char code;

    pipe(_pipe_p);
    pipe(_pipe_c);

    if (child_pid = fork()) {
        close(_pipe_p[0]);
        close(_pipe_c[1]);

        signal(sig, HDL_SIG);
        code = CODE_GO;
        write(_pipe_p[1], &code, 0x1);

        while(read(_pipe_c[0], &code, 0x1) > 0) {
            break;
        }

        wait((int *)0);
        signal(sig, SIG_DFL);
    } else {

        close(_pipe_c[0]);
        close(_pipe_p[1]);

        signal(SIGUSR1, HDL_SIGUSR1);
        code = CODE_GO;
        write(_pipe_c[1], &code, 0x1);

        while(read(_pipe_p[0], &code, 0x1) > 0) {
            break;
        }

        while(true) {
            pause();
        }

        exit(0);
    }
}
