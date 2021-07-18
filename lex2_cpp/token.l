%{
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
extern int put_string(char *str, int len);

/* definitions */
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
int yylval;
vector<string> string_table;
int string_table_index = 0;
int yyline = 1, yycolumn = 1;
%}

delim   [ \t]
ws      {delim}+
letter [a-zA-Z]
digit  [0-9]
id     {letter}({letter}|{digit})*
number {digit}+

%%
\n        {yyline++;yycolumn=1;}
{ws}      {yycolumn += yyleng;}
if        {yycolumn += yyleng;return (IFNUM);}
then      {yycolumn += yyleng;return (THENNUM);}
[bB][eE][gG][iI][nN] {yycolumn += yyleng; return (BEGINNUM);}
end       {yycolumn += yyleng; return(ENDNUM);}
program   {yycolumn += yyleng; return(PROGRAMNUM);}
is        {yycolumn += yyleng; return(ISNUM);}
{id}      {  yycolumn += yyleng;
             yylval = put_string(yytext, yyleng); 
             return (IDNUM);
          }
{number}  {yylval = atoi(yytext); yycolumn += yyleng;return (INTEGERCONST);}
'[^'\n]*    {int c;
           yycolumn += yyleng;
           if (yyleng == 2) {
              yylval = put_string(yytext+1, yyleng-1);
              c=yyinput(); /* read the additional ' */
              if (c != '\'') {
                cout << 
                "unenclosed character, line = " << yyline << ", column ="
               <<  yycolumn-yyleng << "\n";
                if (c != 0) unput(c);
              } 
              return(CHARCONST);
           } else {
              yylval = put_string(yytext+1, yyleng-1);
              c= yyinput();
              if (c != '\'') {
                cout << "unended string, line = "  
                     << yyline << ", column = "
                     << yycolumn-yyleng << "\n";
                if (c != 0) unput(c);
              } 
              return(STRINGCONST);
           }
          }
\+         {yycolumn += yyleng;return (PLUSNUM);}
"*"       {yycolumn += yyleng;return (TIMESNUM);}
"="       {yycolumn += yyleng;return(EQUALNUM);}
.         {
           printf("Unknown character %s, line = %d, column = %d\n", 
           yytext, yyline, yycolumn);yycolumn += yyleng;}

%%

int yywrap()
{  if (feof(stdin)) return 1;
   return 0;
}

int put_string(char *str, int len)
{
  string s(str);
  string_table.push_back(s);
  string_table_index++;
  return string_table_index-1; 
} 




