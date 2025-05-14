#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h> 

int zombie_count = 0;

void clean(int signal) { 
    int status;
    pid_t pid;
    
    // cleaning until no more zombies are left
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        zombie_count--;
        printf("Zombie process %d destroyed  ", pid);
    }

    if (zombie_count == 0) {
        printf("All zombies destroyed.");
    }
}

int main(int argc, char *argv[]) { 


    // code to prcoess command line arguments in terms of argc and argv
// something to compare cli arguments to run block of code
// validate argument count (arg[c]), ensuring arguemnts is --n for arg[1], and making sure argument is not negative in arg[2], aka number of zombies
// for loop to create forks


    if (argc != 3 || strcmp(argv[1], "--n") != 0) {  
        fprintf(stderr, "error in inputs\n");  
        return 1; 
    }

    int arg2 = atoi(argv[2]); 

    if (arg2 <= 0) {  
        fprintf(stderr, "negative amount of zombies inputted\n");
        return 1; 
    }


    signal(SIGCONT, clean);  // Sigcont is to be spcified? 

    // Create zombie processes loop 
    for (int create = 0; create < arg2; create++) { 
        pid_t pid = fork(); 
        if (pid == 0) { 
            // print pid of child process

            printf(getpid());

            exit(0); 
        } else if (pid > 0) { 
            // parent process
            zombie_count++; 
        } else {
            // Error occurred during fork
            fprintf(stderr, "error");
            return 1;
        }
    }
//message sent once parent waiting on clean
    fprintf(stdout, "Parent process waiting on Signal to clean zombies\n");

    
    sleep(1); // need to allow time for zombies to exist before cleaning - without this it seems a zombie is created after the clean, leaving one remaining

    // 
    kill(getpid(), SIGCONT);

    // Parent process waits indefinitely for child process signals
    while (1) {
        pause();  // Wait for signal, also in the grading rubric so
    }

    return 0;
}
