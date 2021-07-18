%{
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
int put_string(char *str, int len);

/* definitions */
int yylval;
float floatNum;
vector<string> string_table;
int string_table_index = 0;
int yyline = 1, yycolumn = 1;
%}
/*辅助定义*/
id [_A-Za-z][_A-Za-z0-9]*
int [1-9]+
float [-+]?[0-9]*[.][0-9]+([eE][+-]?[0-9]*|[0])?


/*规则部分：正规表达式+动作， 词法分析器识别出一个单词后，将该单词对应的字符串保存在 yytext中，其长度为yyleng*/
%%
 /*注释处理 单行+多行*/
\/\/[^\n]*  {cout << "SING_LINE"<< "\n";}//匹配单行注释的正则表达式
\/\*[^*]*\*+([^/*][^*]*\*+)*\/ {cout << "MUL_LINE"<< "\n";}//匹配多行注释的正则表达式
{int} {yylval=atoi(yytext);yycolumn += yyleng;cout << "INT_VAL, " << yylval << "\n";}
{float} {floatNum=atof(yytext); yycolumn += yyleng;cout << "FLOAT_VAL, " << floatNum << "\n";}
(int|float|char|return|if|else|while|for) {yycolumn += yyleng;cout << "keyword,"<<yytext<< "\n"; }
{id} {  yycolumn += yyleng;
             yylval = put_string(yytext, yyleng); 
             cout << "ID, " << string_table[yylval] << "\n";
          }
\*{id} {yycolumn += yyleng;cout<<yytext<<endl;}

";" {yycolumn += yyleng;cout << "SEMI,"<<yytext<<"\n";}
"," {yycolumn += yyleng;cout << "COMMA,"<<yytext<<"\n";}
">"|"<"|">="|"<="|"=="|"!=" {yycolumn += yyleng; cout << "RELOP,"<<yytext<<"\n";}
"=" {yycolumn += yyleng;cout << "ASSIGNOP,"<<yytext<<"\n";}
"+" {yycolumn += yyleng;cout << "PLUS,"<<yytext<<"\n"; }
"-" {yycolumn += yyleng;cout << "MINUS,"<<yytext<<"\n";}
"+=" {yycolumn += yyleng;cout << "COMADD,"<<yytext<<"\n";}
"-=" {yycolumn += yyleng;cout << "COMSUB,"<<yytext<<"\n";}
"++" {yycolumn += yyleng;cout<<"AUTOADD,"<<yytext<<"\n";}
"--" {yycolumn += yyleng;cout << "AUTOSUB,"<<yytext<<"\n";}
"*" {yycolumn += yyleng;cout << "STAR,"<<yytext<<"\n";}
"/" {yycolumn += yyleng;cout << "DIV,"<<yytext<<"\n";}
"&&" {yycolumn += yyleng;cout << "AND,"<<yytext<<"\n";}
"||" {yycolumn += yyleng;cout << "OR,"<<yytext<<"\n";}
"!" {yycolumn += yyleng;cout << "NOT,"<<yytext<<"\n";}
"(" {yycolumn += yyleng;cout << "LP,"<<yytext<<"\n";}
")" {yycolumn += yyleng;cout << "RP,"<<yytext<<"\n";}
"[" {yycolumn += yyleng;cout << "LB,"<<yytext<<"\n";}
"]" {yycolumn += yyleng;cout << "RB,"<<yytext<<"\n";}
"{" {yycolumn += yyleng;cout << "LC,"<<yytext<<"\n";}
"}" {yycolumn += yyleng;cout << "RC,"<<yytext<<"\n";}
[\n] {yyline++;yycolumn=1;}
[ \r\t] {yycolumn+=yyleng;}
'[^\n]{0,1}' { yycolumn += yyleng;cout<<"char_val "<<cout<<*yytext+1<<endl; }
.   {
           printf("Unknown character %s, line = %d, column = %d\n", 
           yytext, yyline, yycolumn);yycolumn += yyleng;}


%%
int main(int argc,char *argv[]){
   yyin=fopen(argv[1],"r");
   yylex();
   fclose(yyin);
   return 0;
}

int put_string(char *str, int len)
{
  string s(str);
  string_table.push_back(s);
  string_table_index++;
  return string_table_index-1; 
} 
