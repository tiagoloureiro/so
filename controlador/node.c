#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[]){
  if(argc == 4 && strcmp(argv[2], "const") == 0){
    printf("const\n");
  }else if(argc == 6 && strcmp(argv[2], "filter") == 0){
    printf("filter\n");
  }else if(argc == 6 && strcmp(argv[2], "window") == 0){
    printf("window\n");
  }else if(argc > 3 && strcmp(argv[2], "spawn") == 0){
    printf("spawn\n");
  }

  printf("ola\n" );

  return 0;
}
