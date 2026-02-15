all: compile run

compile:
	gcc -Wall -Wextra -g -o ./out/main main.c

run:
	./out/main

clear:
	rm -f ./out/main
