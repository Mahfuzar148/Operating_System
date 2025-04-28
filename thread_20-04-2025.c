#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
const int x = 0;
void *addition(){
const int y = 5;
  for(int i = 0; i < 10; i++){
    printf("Addition Thread %d\n" , i);
    x++;
    int processor_no = sched_getcpu();
    printf("Addition Processor: %d  x: %d\n",processor_no , x);
  }
}
void *subtraction(){
  for(int i = 0; i < 5; i++){
    printf("Subtraction Thread %d\n" , i);
    x--;
    int processor_no = sched_getcpu();
    printf("Subtraction Processor: %d  x: %d\n",processor_no , x);
  }
}

void values(){
  printf("x:  %d \n", x);
}
void main(){
  pthread_t tid1,tid2;
  
  // Create a thread
  pthread_create(&tid1, NULL , &addition , NULL);
  pthread_create(&tid2, NULL , &subtraction , NULL);
  for(int i = 0; i < 10; i++){
    printf("Main Thread %d\n" , i);
    int processor_no = sched_getcpu();
    printf("Main Processor: %d  x : %d\n",processor_no, x); 
  }
  // To force main thread to wait until sub-thread is not complete
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  values();
}
