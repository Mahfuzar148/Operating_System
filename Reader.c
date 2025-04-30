// Read a message from named pipe and print it to the screen
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
int main(){
    char buffer[80];
    char msg[] = "Reading from named pipe: \n";

    // Open a named pipe in read mode
    int status;
    status = open("/home/noob_coder/Desktop/P3S2/OS/NamedPipe", O_RDONLY);
    if(status < 0){
        perror("File Open: ");
        exit(EXIT_FAILURE);
    }

    // Read message from a named pipe
    read(status , buffer , sizeof(buffer));
    write(1, msg , strlen(msg));
    write(1, buffer , strlen(buffer));
    close(status);
    exit(EXIT_SUCCESS);
}