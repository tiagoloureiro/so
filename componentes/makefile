all: lib comp_const comp_filter comp_window run_teste

lib:
	@gcc -o funcoes.o -c funcoes.c

run_teste:
	@echo "# Componentes"
	@echo "#######"
	@echo "# 1.1 #"
	@echo "#######"
	@./const 10 < config
	@echo "#######"
	@echo "# 1.2 #"
	@echo "#######"
	@./filter 2 "<" 4 < config
	@echo "#######"
	@echo "# 1.3 #"
	@echo "#######"
	@./window 4 avg 2 < config

comp_const:
	@gcc const.c funcoes.o -o const

comp_filter:
	@gcc filter.c funcoes.o -o filter

comp_window:
	@gcc window.c funcoes.o -o window
