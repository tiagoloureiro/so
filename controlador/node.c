#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#include <limits.h>

int node(char* id, char* argv[]){
  char str_in[PIPE_BUF];
  char str_out[PIPE_BUF];
  int stdin_original = dup(0);
  int stdout_original = dup(1);

  strcpy(str_in, "pipe_");
  strcat(str_in, id);

  int in = 0;
  int out = 1;

  while(1){
    in = open(str_in, O_RDONLY);
    if(in < 0) _exit(0);

    read(in, str_in, PIPE_BUF);

    if( strcmp(str_in, "connect") ){
      strcpy(str_out, "pipe_");
      strcat(str_out, str_in+8);

      out = open(str_out, O_WRONLY);
      if(out < 0) _exit(0);

      printf("connect id: %s to %s\n", id, str_in+8);

      dup2(in, 0);
      dup2(out, 1);

    }else if( strcmp(str_in, "disconnect") ){
      printf("disconnect id: %s\n", id);

      dup2(stdin_original, in);
      dup2(stdout_original, out);
      _exit(0);
    }else if( strcmp(str_in, "inject") ){
      printf("inject id: %s\n", id);
      if( strcmp(argv[0], "window") == 0 ){
        // window
        execvp(argv[0], argv+1);
      }else if( strcmp(argv[0], "filter") == 0 ){
        // filter
        execvp(argv[0], argv+1);
      }else if( strcmp(argv[0], "spawn") == 0 ){
        // spawn
        execvp(argv[0], argv+1);
      }else if( strcmp(argv[0], "const") == 0 ){
        // const
        execvp(argv[0], argv+1);
      }else if( strcmp(argv[0], "tee") == 0){
        // tee
        execvp(argv[0], argv+1);
      }
    }
  }

  return 0;
}
