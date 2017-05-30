CONTROLADOR=controlador/controlador
COMPONENTES=controlador/componentes/const controlador/componentes/filter controlador/componentes/spawn controlador/componentes/window
BIBLIOTECAS=controlador/componentes/funcoes.o

all: remove modulos

modulos:
	@cd controlador/componentes && $(MAKE) componentes -s
	@cd controlador && $(MAKE) -s

remove:
	@rm -f $(CONTROLADOR) $(COMPONENTES) $(BIBLIOTECAS)
