#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); \
                    } while (0)

#define buffSize 2     // Maximum size for the buffer
#define maxBuff 10     // Number of times the buffer will accept values
#define SHM_KEY 0x1111

// Define a structure that will be imposed on the shared memory object

struct sharedMem {
    sem_t  sem1;            // unnamed semaphore
    sem_t  sem2;            // unnamed semaphore
    char   buf[buffSize];   // Data being transferred
};
