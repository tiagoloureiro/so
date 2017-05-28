#include "node.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <limits.h>

int node(char* id, char* argv[]){
  char str[PIPE_BUF];

  strcpy(str, "pipe_");
  strcat(str, id);

  int fd = open(str, O_RDONLY);

  /*while(1){
    read(fd, str, PIPE_BUF);

    //execvp(argv[0], argv+1);
  }*/

  if(id)

  return 0;
}
