#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "./include/waitsig.h"

int main() {

    printf("PID %d\n", getpid());

    waitsig(SIGUSR1);
    waitsig(SIGALRM);
    
    printf("ok!\n");

    return 0;
}
