#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>

int main(int argc, char *argv[]){
  int n = 0, bites = 1;

  if(argc == 2){
    bites = PIPE_BUF;
    char c[bites];

    while (1){
      n = read(0, &c, bites);
      if(n > 0){
        write(1, &c, n);
      }else{
        return 0;
      }
    }
  }

  return 0;
}
