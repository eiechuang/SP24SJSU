 #include <stdio.h>  
#include <stdlib.h>  

#include <unistd.h> //for get pID, fork a child, and pause, which forces pause until sigint
#include <sys/wait.h> // wait to force parent to wait until child, and exit status checkers
#include <signal.h> //Signal handler that manages the sigint in this program.

// This program required the use of a lot of headers that I was completely unfamiliar with; please ignore the header comments above. 

void sigintHandler(int sig) {
    //nothing happens here, because I don't think the instructions say to do anything with this?
}

int main() { 

pid_t pid = fork(); // creates child process

if (pid < 0) {
    perror("fork"); //output an error message
    exit(1);

}
if (pid == 0) {
    signal (SIGINT, sigintHandler);
   printf("Child PID: %d\n", getpid());
    pause (); //this is needed so that the program does not immediately exit before sigint is updated. Alongside the wait command, it should hopefully synchronize the parent and child portions.

    exit(5);


}  else {

    int status; 
    pid_t childpID = wait (&status);

    if (WIFEXITED(status)) {
        // Correctly print the child PID and its exit status
        printf("childpid=%d,exitstatus=%d\n", childpID, WEXITSTATUS(status));  // Correct format
    } 
}

    return 0;
}
