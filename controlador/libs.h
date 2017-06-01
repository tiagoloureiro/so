#ifndef _LIBS_
#define _LIBS_
  #include <limits.h>

  #define NOS 100

  #define VAZIO 0
  #define ABERTO 1

  int estados[NOS];
  int ligacoes[NOS][NOS];
  int in[NOS];
  int out[NOS];
  char comandos[NOS][PIPE_BUF][PIPE_BUF];

  struct no{
    int estado; // VAZIO || ABERTO
    int ligacoes[NOS]; // PARA ONDE ENVIA O OUTPUT
    int in; // DE ONDE LÊ
    int out; //PARA ONDE ESCREVE
    char comando[PIPE_BUF][PIPE_BUF]; // O QUE TEM DE EXECUTAR
  };

  /*typedef struct{
    int estado; // VAZIO || ABERTO
    int ligacoes[NOS]; // PARA ONDE ENVIA O OUTPUT
    int in; // DE ONDE LÊ
    int out; //PARA ONDE ESCREVE
    char comando[PIPE_BUF][PIPE_BUF]; // O QUE TEM DE EXECUTAR
  } no;*/

#endif