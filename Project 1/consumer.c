#include <string.h>
#include "header.h"

int main(){
    int fd;
    struct sharedMem *shmp;

    fd = shmget(SHM_KEY, sizeof(struct sharedMem), 0644 | IPC_CREAT);  //Creating shared memory object    
    if(fd == -1){                                                          
        errExit("Shared Memory");                                               
    }                                                                                                                                             
    
    shmp = shmat(fd, NULL, 0);   //Attatching shared memory to the segment
    if(shmp == (void*)-1){
        errExit("mmap");
    }
    size_t i = 0;
    for(size_t j = 0; j < maxBuff ; j++){
        sem_wait(&shmp->sem1);                   //Waiting for the producer to produce a character                                                
        printf("Got char %c\n", shmp->buf[i]);   //Printing out each produced character(consuming)
        i = i + 1 % buffSize;
        sem_post(&shmp->sem2);                   //Signaling to the producer that an item has been consumed                                                
    }                                            

    exit(EXIT_SUCCESS);

}
