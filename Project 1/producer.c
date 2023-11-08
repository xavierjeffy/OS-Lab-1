#include <ctype.h>
#include "header.h"
#include <pthread.h>

int
main(){
    int fd;
    struct sharedMem *shmp;

    fd = shmget(SHM_KEY, sizeof(struct sharedMem), 0644 | IPC_CREAT);   //Creating shared memory object
    if(fd == -1){                                                          
        errExit("Shared Memory");                                               
    }                                                                                                                                             
    
    shmp = shmat(fd, NULL, 0);   //Attatching shared memory to the segment
    if(shmp == (void*)-1){
        errExit("mmap");
    }
    if(sem_init(&shmp->sem1, 1, 0) == -1){   //Initializing semaphores
        errExit("sem_init-sem1");
    }
    if(sem_init(&shmp->sem2, 1, 2) == -1){                   
        errExit("sem_init-sem2");
    }

    char item = 'a';   
    size_t i = 0;
    for(size_t j = 0; j < maxBuff ; j++){ 
        sem_wait(&shmp->sem2);     //Waiting for the consumer to consume a character                                    
        shmp->buf[i] = item;       //Placing characters into the buffer
        i = (i + 1) % buffSize;
        ++item;
        sem_post(&shmp->sem1);    //Signaling that an item has been produced
    }
  
    
    exit(EXIT_SUCCESS);



    
}
