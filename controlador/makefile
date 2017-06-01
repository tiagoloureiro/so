LIB=componentes/funcoes.c node.c connect.c disconnect.c

all: controlador run

controlador:
	@gcc controlador.c $(LIB) -o controlador

run:
	@./controlador < input_2
