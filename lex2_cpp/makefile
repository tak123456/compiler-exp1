a.out: lex.yy.o main.o
	g++ lex.yy.o main.o -ll
lex.yy.o: token.l
	lex token.l
	g++ -c lex.yy.c
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm -f *.o
	rm -f lex.yy.c
	rm -f *~
	rm -f #*#
	rm -f core*
	rm -f a.out
