#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");

        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        close(pipe1[0]);
        close(pipe2[1]);

        char msg_to_child[100];
        snprintf(msg_to_child, sizeof(msg_to_child), "I am the parent process! and my name is %d\n", getpid());
        write(pipe1[1], msg_to_child, strlen(msg_to_child));


        char msg_from_child[100];
        ssize_t n = read(pipe2[0], msg_from_child, sizeof(msg_from_child) - 1);
        if (n > 0) {

            msg_from_child[n] = '\0';
            printf("%s\n", msg_from_child);
        }

        wait(NULL);

    } else {

        close(pipe1[1]);
        close(pipe2[0]);

        char received_msg[100];

        ssize_t n = read(pipe1[0], received_msg, sizeof(received_msg) - 1);
        if (n > 0) {
            received_msg[n] = '\0';
            printf("%s", received_msg);

        }

        char response[100];
        snprintf(response, sizeof(response), "Daddy, my name is %d", getpid());
        write(pipe2[1], response, strlen(response));
        exit(EXIT_SUCCESS);
    }

    return 0;
}
