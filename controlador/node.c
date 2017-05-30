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

  strcpy(str_in, "pipe_");
  strcat(str_in, id);

  int in = open(str_in, O_RDONLY);
  if(in < 0) _exit(0);

  while(1){
    int out = 1;
    read(in, str_in, PIPE_BUF);

    if( strcmp(str_in, "connect") ){

      strcpy(str_out, "pipe_");
      strcat(str_out, str_in+8);

      out = open(str_out, O_WRONLY);
      if(out < 0) _exit(0);

    }else if( strcmp(str_in, "disconnect") ){

    }else if( strcmp(str_in, "inject") ){
      if( strcmp(argv[0], "window") == 0 ){
        // window
      }else if( strcmp(argv[0], "filter") == 0 ){
        // filter
      }else if( strcmp(argv[0], "spawn") == 0 ){
        // spawn
      }else if( strcmp(argv[0], "const") == 0 ){
        // const
      }else if( strcmp(argv[0], "tee") == 0){
        //execvp();
      }
    }
  }

  return 0;
}

/*int auxiliar(char* str_in, char* str_out, char* argv[], int in){
  strcpy(str_out, "pipe_");
  strcat(str_out, str_in+8);

  int out = open(str_out, O_WRONLY);
  if(out >= 0){
    if( strcmp(argv[0], "window") == 0 ){
      window(argv+1, in, out);
    }else if( strcmp(argv[0], "filter") == 0 ){
      filter(argv+1, in, out);
    }else if( strcmp(argv[0], "spawn") == 0 ){
      spawn(argv+1, in, out);
    }else if( strcmp(argv[0], "const") == 0 ){
      constante(argv+1, in, out);
    }else if( strcmp(argv[0], "tee") == 0){

    }
  }else{
    return -1;
  }

  return 0;
}

int node(char* id, char* argv[]){
  char str_in[PIPE_BUF];
  char str_out[PIPE_BUF];
  int ligacao = 0;

  strcpy(str_in, "pipe_");
  strcat(str_in, id);

  //printf("id: %s | ligado a: %s\n", id, argv[1]);

  int in = open(str_in, O_RDONLY);
  if(in >= 0){

    while(1){
      read(in, str_in, PIPE_BUF);
      if( strstr(str_in, "connect ") ){
      }/*else if( strstr(str_in, "disconnect ") ){

      }else if( strstr(str_in, "inject ") ){

      }else if( strstr(str_in, "command ") ){
        auxiliar(str_in, str_out, argv, in);
      }*/
      /*else{
        auxiliar(str_in, str_out, argv, in);
      }
    }


  }else{
    return -1;
  }


}*/
