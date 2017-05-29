all: remove modulos

modulos:
	@cd controlador && $(MAKE) -s

remove:
	@rm controlador/controlador
