#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]){
  if(argc == 4 && strcmp(argv[2], "const") == 0){
    printf("const\n");
  }else if(argc == 6 && strcmp(argv[2], "filter") == 0){
    printf("filter\n");
  }else if(argc == 6 && strcmp(argv[2], "window") == 0){
    printf("window\n");
  }else if(argc > 3 && strcmp(argv[2], "cut") == 0){
    printf("cut\n");
  }else if(argc > 3 && strcmp(argv[2], "grep") == 0){
    printf("grep\n");
  }else if(argc > 3 && strcmp(argv[2], "tee") == 0){
    printf("tee\n");
  }else if(argc > 3 && strcmp(argv[2], "spawn") == 0){
    printf("spawn\n");
  }

  /*FILE *f = fopen("file.txt", "w");
  if (f == NULL)
  {
      printf("Error opening file!\n");
      exit(1);
  }
  fprintf(f, "Some text\n");*/

  return 0;
}
