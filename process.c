#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <sched.h>
void main(){

    pid_t parentPID, childPID;
    int child_status,process_no;
    
    parentPID = getpid();
    for(int i = 0;1000; i++){
    child_status = fork();
    
      if(child_status == 0){ // Child process
        childPID = getpid();
        process_no = sched_getcpu();
        printf("Parent-PID: %u, Child-PID: %u\n Child Processor: %d\n", parentPID, childPID,process_no);
      }else{ // Parent process
        process_no = sched_getcpu();
        printf("Parent-PID: %u\n Parent Processor: %d\n",parentPID,process_no);
      }
    }
}
