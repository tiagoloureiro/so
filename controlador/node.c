#include "node.h"
#include "componentes/window.h"
#include "componentes/filter.h"
#include "componentes/const.h"
#include "componentes/spawn.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#include <limits.h>

int node(char* id, char* argv[]){
  char str[PIPE_BUF];
  int ligacao = 0;

  strcpy(str, "pipe_");
  strcat(str, id);

  int in = open(str, O_RDONLY);
  if(in >= 0){
    /*printf("%s -> ", id);
    for(int i=0; argv[i]; i++)
      printf("%s ", argv[i]);
    printf("\n");*/

    while(1){
      read(in, str, PIPE_BUF);
      if( strstr(str, "connect ") ){
        break;
        ligacao = atoi(str+8);
      }
    }

    strcpy(str, "pipe_");
    strcat(str, str+8);

    int out = open(str, O_WRONLY);

    window(argv, in, out);

    return 0;
  }else{
    return -1;
  }


}
