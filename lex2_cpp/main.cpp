#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define STRINGCONST 1
#define INTEGERCONST 2
#define CHARCONST 3
#define PLUSNUM 4
#define TIMESNUM 5
#define IFNUM 6
#define THENNUM 7
#define ELSENUM 8
#define EQUALNUM 9
#define IDNUM 10
#define PROGRAMNUM 11
#define ISNUM 12
#define BEGINNUM 13
#define ENDNUM 14


extern int yylval;
extern vector<string> string_table;
extern int yylex();
int main()
{
  int i;
  while (true) {
    i=yylex();
    switch(i) {
    case IDNUM: { 
      cout << "IDNUM, " << string_table[yylval] << "\n";
      break;}
    case STRINGCONST: {
      cout << "STRINGCONST, " << string_table[yylval] << "\n";
      break;}
    case INTEGERCONST: {
      cout << "INTEGERCONST, " << yylval << "\n";
      break;}
    case CHARCONST: {
      cout << "CHARCONST, " << string_table[yylval] << "\n"; 
      break;}
    case PLUSNUM: {
      cout << "PLUSNUM\n"; break;}
    case TIMESNUM: {
      cout << "TIMESNUM\n"; break;}
    case IFNUM: { cout << "IFNUM\n"; break;}
    case THENNUM: { cout << "THENNUM\n"; break;}
    case ELSENUM: { cout << "ELSENUM\n"; break;}
    case EQUALNUM: { cout << "EQUALNUM\n"; break;}
    case PROGRAMNUM: { cout << "PROGRAMNUM\n"; break;}
    case ISNUM: { cout << "ISNUM\n"; break;}
    case BEGINNUM: { cout << "BEGINNUM\n"; break;}
    case ENDNUM: { cout << "ENDNUM\n"; break;}
    default: {cout << "Unknown token: " << i << "\n";}
    }
  }
  return 0;
}


