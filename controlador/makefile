all: lib controlador run

controlador:
	@gcc controlador.c node.o -o controlador

lib:
	@gcc -o node.o -c node.c

run:
	@./controlador < input
