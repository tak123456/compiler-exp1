%{
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* definitions */

%}
/*辅助定义*/
%%
[a-z] {int idx=(int)(*yytext-'a');char ch=(idx+13)%26+97;cout<<ch;}
[A-Z] {int idx=(int)(*yytext-'A');char ch=(idx+13)%26+65;cout<<ch;}
[^a-zA-Z] {cout<<*yytext;}


%%
int main(int argc,char *argv[]){
   yyin=fopen(argv[1],"r");
   yylex();
   fclose(yyin);
   return 0;
}
 
