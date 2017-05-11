all: lib comp_const comp_filter run

lib:
	gcc -o funcoes.o -c funcoes.c

run:
	@echo "# Componentes"
	@echo "# 1.1"
	@./const 10 < config
	@echo "# 1.2"
	@./filter 2 "<" 4 < config

comp_const:
	gcc const.c funcoes.o -o const

comp_filter:
	gcc filter.c funcoes.o -o filter
