a.out: lex.yy.o 
	g++ lex.yy.o  -ll 
lex.yy.o: lexer.l
	lex lexer.l
	g++ -c lex.yy.c
clean:
	rm -f *.o
	rm -f lex.yy.c
	rm -f *~
	rm -f #*#
	rm -f core*
	rm -f a.out
