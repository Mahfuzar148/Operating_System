#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sched.h>
#include <string.h>

void main(){
  pid_t pid;
  int processor_no;
  int pipe_fd[2], pipe_fd1[2];// Pipe Descriptor
  char buffer[80];
  
  //Create an unnamed pipe
  printf("Pipe Description: %d, %d\n",pipe_fd[0], pipe_fd[1]);
  //for(int i = 0; i < 1000; i++){
      pipe(pipe_fd);
      printf("Pipe Description: %d, %d\n",pipe_fd[0], pipe_fd[1]);
  //}
  
  /*
    File Descriptor:
      0: standard input (stdin/keyboard)
      1: standard output(stdout/monitor)
      2: Standard error(stderr)
  */
  
  //Create a child
  pid = fork();
  
  if(pid < 0){
    perror("Fork");
    exit(EXIT_FAILURE);
  }else if(pid == 0){ //Child process
    pid = getpid();
    processor_no = sched_getcpu();
    printf("Child PID: %d, Processor Number: %d\n", pid, processor_no);
    
    char *msg = "Type a message for the Parent: ";
    write(1, msg, strlen(msg));
    read(0, buffer, sizeof(buffer));
    
    //Write Child message to the pipe
    close(pipe_fd[0]); // Close write_end of the pipe
    write(pipe_fd[1], buffer, strlen(buffer)); 
    close(pipe_fd[1]); //Close write_end of the pipe
    
  }else{  //Parent Process
    pid = getpid();
    processor_no = sched_getcpu();
    printf("Parent PID: %d, Processor Number: %d\n", pid, processor_no);
    
    //Read Child's message from the pipe
    close(pipe_fd[1]);// Close write_end of the pipe
    read(pipe_fd[0], buffer, sizeof(buffer));
    close(pipe_fd[0]);//Close write_end of the pipe
    
    write(1, buffer, strlen(buffer));
    //Wait for the termination of Child process in order to avoid making them Orphan Processes
    int status;
    wait(&status);
  }
  exit(EXIT_SUCCESS);
}
