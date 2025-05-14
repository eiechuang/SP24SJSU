#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;

int turn = 1; // 1 for thread 1, 2 for thread 2
int running = 1;

void handle_sigint(int sig) {
    running = 0;
    // Wake up both threads 
    pthread_cond_broadcast(&cond1);
    pthread_cond_broadcast(&cond2);
}

void* thread1_func(void* arg) {
    while (running) {
        pthread_mutex_lock(&mutex);
        while (turn != 1 && running)
            pthread_cond_wait(&cond1, &mutex);

        if (!running) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        printf("thread 1: ping thread 2\n");
        fflush(stdout);
        turn = 2;
        pthread_cond_signal(&cond2);

        while (turn != 1 && running)
            pthread_cond_wait(&cond1, &mutex);

        if (!running) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        printf("thread 1: pong! thread 2 ping received\n");
        fflush(stdout);
        turn = 2;
        pthread_cond_signal(&cond2);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* thread2_func(void* arg) {
    while (running) {
        pthread_mutex_lock(&mutex);
        while (turn != 2 && running)
            pthread_cond_wait(&cond2, &mutex);

        if (!running) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        printf("thread 2: pong! thread 1 ping received\n");
        fflush(stdout);
        printf("thread 2: ping thread 1\n");
        fflush(stdout);
        turn = 1;
        pthread_cond_signal(&cond1);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    signal(SIGINT, handle_sigint);

    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread1_func, NULL);
    pthread_create(&t2, NULL, thread2_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
