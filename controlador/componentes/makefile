all: componentes

componentes: lib const window filter spawn

lib:
	@gcc -o funcoes.o -c funcoes.c

const:
	@gcc const.c funcoes.o -o const

window:
	@gcc window.c funcoes.o -o window

filter:
	@gcc filter.c funcoes.o -o filter

spawn:
	@gcc spawn.c funcoes.o -o spawn
