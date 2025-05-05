/*
  Shared Memory
    1. Create/Get access shared memory segment: shmget() to get an id
    2. Attach to the shared memory: shmat()
    3. Detach from the shared memory after finishing usage: shmdt()
    4. Remove shared memory: shmctl()
    
    Message Queue:
    1. Create/get access of a message queue: msgget()
    2. send/receive message: msgsnd() and msgrcv()
    3. Remove message queue: msgctl()
*/
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

int main(){
  
  // int msgget(key_t key, int msgflg);
  key_t key = 1234;
  int msgid = msgget(key, IPC_CREAT|0666);

  struct  msg_queue
  {
    /* data */
    int type;
    char text[100];
  }msg;
  
  
  pid_t pid;
  pid = fork();
  
  if(pid == 0){ // Child
    printf("Child process\n");
    // Send message
    msg.type = 1;
    sprintf(msg.text, "Hello Parent\n");
    // int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
    msgsnd(msgid, &msg, sizeof(msg), 0);
    
    //printf("Child received: %s\n", msg.text);
  }else{ // Parent
    printf("Parent process\n");
    int status;
    wait(&status);

    // Receive message
    msgrcv(msgid, &msg, sizeof(msg), 1, 0);
    printf("Parent received: %s\n", msg.text);

    // Remove message queue
    // int msgctl(int msqid, int cmd, struct msqid_ds *buf);
    msgctl(msgid, IPC_RMID, NULL);
    printf("Message queue removed\n");
  }
  exit(EXIT_SUCCESS);
}
