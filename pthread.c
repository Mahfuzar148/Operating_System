#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>

void *subtraction() {
    //for(int i = 1; i < 1000000; i++){}
    int processor_no;
    processor_no = sched_getcpu();
    printf("Subtraction Thread %d\n",processor_no);
    
}

void *addition() {
    // for(int i = 1; i < 10; i++){}
    int processor_no;
    processor_no = sched_getcpu();
    printf("Addition Thread %d\n",processor_no);
}

int main() {
    pthread_t TID1,TID2;
    int retVal;
    pthread_create(&TID1,NULL,&subtraction, NULL);
    pthread_create(&TID2,NULL,&addition, NULL);
    pthread_join(TID1,NULL);
    pthread_join(TID2,NULL);
    
    int processor_no = sched_getcpu();
    printf("Main thread: %d\n",processor_no); 
  
    return 0;
}

