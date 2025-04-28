// Read a message from keyboard  and write it to a named pipe

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
int main(){
    char buffer[80];
    char msg[] = "Type a message for other Process: \n";

    // Read message from Keyboard
    write(1, msg , strlen(msg));
    read(0, buffer , sizeof(buffer));

    // Open a named pipe in read mode
    int status;
    char *named_pipe_path = "/home/noob_coder/Desktop/P 3 S 2/OS/NamedPipe";
    status = open(named_pipe_path, O_WRONLY);

    if(status < 0){
        perror("File Open: ");
        exit(EXIT_FAILURE);
    }
    
    // Write read message to a named pipe
    write(status , buffer , strlen(buffer));
    close(status);
    exit(EXIT_SUCCESS);
}