
#include <stdio.h>
#include <string.h>

#include <unistd.h>

int main(int argc, char* argv[]){
  char *buf = NULL;
  char *pal;
  ssize_t n;

  while((n = getline(&buf, &n, stdin)) != -1){
    memcpy(pal, buf, n);
    pal[n-1] = '\0';
    int tam = sprintf(pal, "%s:%s\n", pal, argv[1]);

    write(1, pal, tam);
  }

  return 0;
}
