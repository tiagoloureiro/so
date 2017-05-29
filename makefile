all:
	@cd controlador && $(MAKE) -s
	@cd componentes && $(MAKE) -s

remove:
	@cd controlador && rm node.o 
