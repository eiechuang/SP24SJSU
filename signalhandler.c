#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int debug_mode = 0;  // debug printing flag. 0 means no printing, 1 goes into the loop
int i = 0;   // Track iteration counter


void signal_handler(int sig) {
    if (sig == SIGINT) {
        debug_mode = !debug_mode;  // Toggle debug mode on off, like a switch
    } else if (sig == SIGUSR1) {
        printf("SIGUSR1 received.");
        exit(0);
    }
}

int main() { //registering signal handlers in mian 
    signal(SIGINT, signal_handler);
    signal(SIGUSR1, signal_handler);

    while (1) {
        i++;
        if (debug_mode) {
            printf("Iteration: %d\n", i);
        }
        sleep(2);
    }

    return 0;
}