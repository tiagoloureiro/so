#include "connect.h"

#include <fcntl.h>
#include <unistd.h>

#include <limits.h>

#include <stdio.h>
#include <string.h>

int connect(char** argumentos){
  char str[PIPE_BUF];

  for(int i=0; argumentos[i+1]; i++){
    char pipe[PIPE_BUF];

    strcpy(str, "connect ");
    strcat(str, argumentos[i+1]);

    strcpy(pipe, "pipe_");
    strcat(pipe, argumentos[0]);

    int fd = open(pipe, O_WRONLY);

    write(fd, str, strlen(str));

    //printf("id: %s ligado a: %s\n", argumentos[0], argumentos[i+1]);

    //close(fd);
  }
}
