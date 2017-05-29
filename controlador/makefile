COMPONENTES=componentes/funcoes.c componentes/window.c componentes/const.c componentes/filter.c componentes/spawn.c
LIB=node.c
all: controlador run

controlador:
	@gcc controlador.c $(LIB) $(COMPONENTES) -o controlador

run:
	@./controlador < input
