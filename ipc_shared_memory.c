
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#define SHM_SIZE 4096

int generate_random(int lower, int upper) {
    return rand() % (upper - lower + 1) + lower;
}

int main() {
    pid_t pid;
    char *shared_data;
    int shm_id;

    srand(time(NULL));

    shm_id = shmget(IPC_PRIVATE, SHM_SIZE, S_IRUSR | S_IWUSR);
    if (shm_id < 0) {
        perror("Failed to create shared memory");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    else if (pid == 0) {
        shared_data = shmat(shm_id, NULL, 0);
        if (shared_data == (void *) -1) {
            perror("Child failed to attach shared memory");
            exit(EXIT_FAILURE);
        }

        printf("Consumer started. Waiting for messages...\n");
        while (1) {
            if (strlen(shared_data)) {
                printf("Received: %s\n", shared_data);
                shared_data[0] = '\0';
            } else {
                printf("No message to receive.\n");
            }
            sleep(3);
        }

        shmdt(shared_data);
        exit(EXIT_SUCCESS);
    }

    else {
        shared_data = shmat(shm_id, NULL, 0);
        if (shared_data == (void *) -1) {
            perror("Parent failed to attach shared memory");
            shmctl(shm_id, IPC_RMID, NULL);
            exit(EXIT_FAILURE);
        }

        printf("Producer started. Sending messages...\n");
        while (1) {
            int num = generate_random(1, 100);
            sprintf(shared_data, "%d", num);
            printf("Sent: %d\n", num);
            sleep(3);
        }

        shmdt(shared_data);
        shmctl(shm_id, IPC_RMID, NULL);
    }

    return 0;
}
