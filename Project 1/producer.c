#include <ctype.h>
#include "header.h"
#include <pthread.h>

int
main(){
    int fd;
    char *shmpath;
    struct sharedMem *shmpath;

    if (argc != 2){
        fprintf(stderr, "Usage; %s /shm-path\n");
        exit(EXIT_FAILURE);
    }
    fd = shm_open("/produer-consumer", O_CREAT | O_EXCL | O_RDWR, 0600);          //creating shared memroy object
    if(fd == -1){                                                          
        errExit("shm_open");                                               
    }                                                                      
    if(ftruncate(fd, sizeof(struct sharedMem)) == -1){                            //mapping the object into the address             
        errExit("ftruncate");                                                     //space of the caller                      
    }
    shmp = mmap(NULL, sizeof(*shmp), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(shmp == MAP_FAILED){
        errExit("mmap");
    }
    if(sem_init(&shmp->sem1, 1, 0) == -1){                                        //Initializing semaphores
        errExit("sem_init-sem1");
    }
    if(sem_init(&shmp->sem2, 1, 0) == -1){
        errExit("sem_init-sem2");
    }
    // if(sem_wait(&shmp->sem1) == -1){                                              //Waiting for sem1 to be posted
    //     errExit("sem_wait");
    // }
    char item = 'a';
    size_t i = 0;
    for(size_t j = 0; j < maxBuff ; j++){                                          //Placing charaters into the buffer
        buf[i] = item;
        i = i + 1 % maxBuff;
        ++item; 
    }
    // if(sem_wait(&shmp->sem2) == -1){                                              //Waiting for sem2 to be posted
    //     errExit("sem_wait");
    // }
    shm_unlink(shmpath);                                                          //Unlinking shared memory object
    exit(EXIT_SUCCESS);





}
