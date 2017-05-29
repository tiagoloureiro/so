all: componentes node controlador run

componentes:
	@cd componentes && $(MAKE) -s

controlador:
	@gcc controlador.c node.o componentes/window.o -o controlador

node:
	@gcc -o node.o -c node.c

run:
	@./controlador < input
