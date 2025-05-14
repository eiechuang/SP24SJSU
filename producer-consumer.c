#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <getopt.h>
#include <errno.h>

#define SHM_NAME "/prod_cons_shm"
#define SEM_EMPTY "/sem_empty"
#define SEM_FULL "/sem_full"
#define SEM_MUTEX "/sem_mutex"
#define MAX_MSG_LEN 256

typedef struct {
    int head;
    int tail;
    int size;
    char messages[][MAX_MSG_LEN];
} SharedQueue;

void print_usage(char *prog) {
    fprintf(stderr,
        "Usage: %s [-p | -c] -q <queue_size> [-m <message>] [-s | -u] [-e]\n", prog);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int is_producer = 0, is_consumer = 0, use_shm = 0, verbose = 0;
    int queue_size = 0;
    char *message = NULL;

    int opt;
    while ((opt = getopt(argc, argv, "pcq:m:sue")) != -1) {
        switch (opt) {
            case 'p': is_producer = 1; break;
            case 'c': is_consumer = 1; break;
            case 'q': queue_size = atoi(optarg); break;
            case 'm': message = optarg; break;
            case 's': use_shm = 1; break;
            case 'e': verbose = 1; break;
            default: print_usage(argv[0]);
        }
    }

    if (queue_size <= 0)
        print_usage(argv[0]);
    if (is_producer && !message)
        print_usage(argv[0]);

    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    size_t shm_size = sizeof(SharedQueue) + queue_size * MAX_MSG_LEN;
    ftruncate(shm_fd, shm_size);
    void *shm_ptr = mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    SharedQueue *queue = (SharedQueue *)shm_ptr;

    // Initialize semaphores
    sem_t *sem_empty = sem_open(SEM_EMPTY, O_CREAT, 0666, queue_size);
    sem_t *sem_full = sem_open(SEM_FULL, O_CREAT, 0666, 0);
    sem_t *sem_mutex = sem_open(SEM_MUTEX, O_CREAT, 0666, 1);

    if (is_producer) {
        sem_wait(sem_empty);
        sem_wait(sem_mutex);

        strncpy(queue->messages[queue->tail], message, MAX_MSG_LEN - 1);
        queue->messages[queue->tail][MAX_MSG_LEN - 1] = '\0';
        queue->tail = (queue->tail + 1) % queue_size;

        if (verbose)
            printf("Produced: %s\n", message);

        sem_post(sem_mutex);
        sem_post(sem_full);
    }

    if (is_consumer) {
        sem_wait(sem_full);
        sem_wait(sem_mutex);

        char consumed[MAX_MSG_LEN];
        strncpy(consumed, queue->messages[queue->head], MAX_MSG_LEN);
        queue->head = (queue->head + 1) % queue_size;

        if (verbose)
            printf("Consumed: %s\n", consumed);

        sem_post(sem_mutex);
        sem_post(sem_empty);
    }

    munmap(shm_ptr, shm_size);
    close(shm_fd);

    return 0;
}

