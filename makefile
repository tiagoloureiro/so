all: remove
	@cd controlador && $(MAKE) -s
	@cd componentes && $(MAKE) -s

remove:
	@find . -name \*.o -delete
