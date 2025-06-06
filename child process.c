#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        printf("Fork failed!\n");
    } else if (pid == 0) {
        // This runs only in child
        printf("I am the Child Process\n");
        printf("Child PID: %d\n", getpid());       // Child's own PID
        printf("Child's Parent PID: %d\n", getppid()); // PID of parent
    } else {
        // This runs only in parent
        printf("I am the Parent Process\n");
        printf("Parent PID: %d\n", getpid());       // Parent's own PID
        printf("Child PID from fork(): %d\n", pid); // PID of child (returned by fork)
    }

    return 0;
}
