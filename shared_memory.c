// Shared memory example
// This program demonstrates the concept of shared memory in C.
// It creates a child process using fork() and shows how local and global variables are handled in both processes.
// The program prints the values and addresses of local and global variables in both the parent and child processes.
// It also modifies the values of these variables in both processes to show that they are independent.
// But the addresses of the variables remain the same in both processes.


//shmget()
//mmap()
//1. Create shared memory segment by shmget()
//2. Attach to the shared memory by shmat()
//3. Use the shared memory
//4. Detach from the shared memory by shmdt()
//5. Remove the shared memory segment by shmctl()

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>

int global_var = 10;

void main(){
    int local_var = 20;

    int *local_address, *global_address;

    local_address = &local_var;
    global_address = &global_var;

    // Shared memory space
    //int shmget(key_t key, size_t size, int shmflg);
        key_t key = 1234;
        int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        int *shm_addr = &shmid;
        printf("Shared Memory ID: %d\n", shmid);
        printf("Shared Memory Address: %p\n", shm_addr);

        if(shmid == -1){
            perror("shmget: ");
            exit(EXIT_FAILURE);
        }


    // Create child process
    pid_t pid = fork();

    if(pid == -1){
        perror("Fork:");
        exit(EXIT_FAILURE);
    }else if(pid == 0){ // Child process

        printf("Child Process \n");
        //printf("Local Variable : %d\nGlobal Variable : %d\n", local_var, global_var);
        //printf("Local Address : %p\nGlobal Address : %p\n",  local_address,  global_address);

        local_var = 100;
        global_var = 200;
        printf("Local Address : %p\nGlobal Address : %p\n",  local_address,  global_address);

        // Attach to the shared memory
        // void *shmat(int shmid, const void *_Nullable shmaddr, int shmflg);
        void *shm_addr = shmat(shmid, NULL, 0);
        if(shm_addr == (int *) -1){
            perror("shmat:");
            exit(EXIT_FAILURE);
        }

        // Put value into shared memory
        int *shared_var = shm_addr;
        *shared_var = 300;
        printf("Shared Variable : %d\n", *shared_var);
        printf("Attached to shared memory: %p\n", shm_addr);


        // Detach child from the shared memory
        // int shmdt(const void *shmaddr);
        int status = shmdt(shm_addr);
        if(status == -1){
            perror("shmdt:");
            exit(EXIT_FAILURE);
        }

    }else{ // Parent process

        printf("Parent Process \n");
        //printf("Local Variable : %d\nGlobal Variable : %d\n", local_var, global_var);
        //printf("Local Address : %p\nGlobal Address : %p\n",  local_address,  global_address);

        local_var = 100;
        global_var = 200;
        printf("Local Address : %p\nGlobal Address : %p\n",  local_address,  global_address);

        // Attach to the shared memory
        // void *shmat(int shmid, const void *_Nullable shmaddr, int shmflg);
        void *shm_addr = shmat(shmid, NULL, 0);
        if(shm_addr == (int *) -1){
            perror("shmat:");
            exit(EXIT_FAILURE);
        }

        // Put value into shared memory
        int *shared_var = shm_addr;
        *shared_var = 45;
        printf("Shared Variable : %d\n", *shared_var);
        printf("Attached to shared memory: %p\n", shm_addr);


        // Detach child from the shared memory
        // int shmdt(const void *shmaddr);
        int status = shmdt(shm_addr);
        if(status == -1){
            perror("shmdt:");
            exit(EXIT_FAILURE);
        }

    }
    exit(EXIT_SUCCESS);
}