all:
	@find . -name \*.o -delete
	@cd controlador && $(MAKE) -s

remove:
	@find . -name \*.o -delete
