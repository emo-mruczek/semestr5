all: astyle main

main: main.c
	gcc -Wpedantic -Wall -Wextra -o main main.c

astyle:
	astyle --style=attach --break-blocks --pad-oper --pad-header --align-pointer=type --align-reference=name main.c

clean: 
	trash main
