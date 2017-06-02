LIB=componentes/funcoes.c node.c connect.c disconnect.c

all: controlador run
all_2: controlador run_2
controlador:
	@gcc controlador.c $(LIB) -o controlador

run:
	@./controlador < input

run_2:
	@./controlador < input_2
