all: comp_const run

run:
	echo "# Componetes"
	echo "# 1.1\n"
	./const 10 < config
	echo "# 1.2\n"
	./filter 2 < 4 < config

comp_const:
	gcc const.c -o const

comp_filter:
	gcc filter.c -o filter
