.PHONY: 3

1:
	flex ex1.lex
	gcc -o 1 lex.yy.c -lfl

2: 
	flex ex2.lex
	gcc -o 2 lex.yy.c -lfl

3:
	flex ex3.lex
	gcc -o 3 lex.yy.c -lfl

4:
	flex ex4.lex
	gcc -o 4 lex.yy.c -lfl -lm

.PHONY: clean

clean:
	rm 1 2 3 4 lex.yy.c


