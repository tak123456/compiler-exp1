#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;
static string critical_words[12] = {"int","double","char","float"};
string txt; //��Ŷ���Ĵ����
string word; //��Ź��ɵ��ʵ��ַ���
string word1; //��������float��e��������
int type=-2; //�ֱ���
int line; //��¼����
int number; //�������
int demical; //���С������
char ch; //���ÿ�ζ�����ַ�
char reg; //������
char reg1; //e����������
int flag1=1; //ѭ���ж�һ�Σ�����޴�������
int errorline=1; //������
string errstr; //�����ַ�
int flagcount=0;

int check()
{
    int pos = 0;
    do{                     //����ִ��һ��
        errstr.clear();
        ch = txt[pos++];
        if(ch == '\n')
            errorline++;
    }while(ch == ' '||ch == '\n');

    while(ch!='\0'){
        errstr += ch;
        if(ch == '\n'){
            errorline++;
        }
        if(ch==' '||ch=='\n'){
            errstr.clear();
        }
        if(ch == 'e' && (txt[pos]==';') && (txt[pos-2]>='0'&&txt[pos-2]<='9'))
        {
            for(int i=0;errstr[i]!='\0';i++){
                if(!(errstr[i]>='0'&&errstr[i]<='9')){
                    flagcount++;
                }
                else{break;}
            }

            cout<<"Error type A at Line "<<errorline<<": Illegal floating point number \"";
            for(int i=flagcount;errstr[i]!='\0';i++){
                cout<<errstr[i];
            }
            cout<<"\"."<<endl;
            return 0;
        }
        ch = txt[pos++];
    }
    return 1;
}




void yylex()
{
    line = 1;
    int pos = 0;
    string str[10];
    str[0]="integer";
    str[1]="decimal";
    str[2]="type";
    str[3]="identify";
    str[4]="fenge";
    str[5]="bracket";
    str[6]="OPT";
    str[7]="float";

    do{                     //����ִ��һ��
        ch = txt[pos++];
        if(ch == '\n')
            line++;
    }while(ch == ' '||ch == '\n');

    while(ch != '\0'){
        while(ch == ' '||ch == '\n'){
            if(ch == '\n'){
                line++;
            }
            ch = txt[pos++];
        }

        if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
            type = 3;
            word += ch;
            ch = txt[pos++];
            while((ch >= 'a'&&ch <= 'z')||(ch >= 'A'&&ch <= 'Z')||(ch >= '0'&&ch <= '9')||(ch == '_')){
                word += ch;
                ch = txt[pos++];
            }
            for(int i = 0;i < 4; i++){
                if(word == critical_words[i]){   //��Ϊ�ؼ���
                    type = 2;
                    cout<<"line"<<line<<":("<<str[type]<<", "<<word<<")"<<endl;
                    word.clear();
                    break;
                }
            }
            if(type == 3){
                cout<<"line"<<line<<":("<<str[type]<<", "<<word<<")"<<endl;
            }
            word.clear();
            type = -2;
        }

        if((ch >= '0')&&(ch <= '9')&&type!=1&&type!=7){
//            bool flag=false;	//�ж��Ƿ�����С������һ��������
            type = 0;
            number = (ch - '0') + number * 10;
            ch = txt[pos++];
            while(ch >= '0' && ch <= '9'){
                number = (ch - '0') + number * 10;
                ch = txt[pos++];
            }
            if(ch == '.'){
                type = 1;
                ch = txt[pos++];
                continue;
            }
            if(!reg)
                cout<<"line"<<line<<":("<<str[type]<<", "<<number<<")"<<endl;
            else
                cout<<"line"<<line<<":("<<str[type]<<", "<<reg<<number<<")"<<endl;
            type = -2;
            number = 0;
        }

        if((ch >= '0')&&(ch <= '9')&&(type==1)&&(type!=7)){
            word += ch;
            ch = txt[pos++];
            while(ch >= '0' && ch <= '9'){
                word += ch;
                ch = txt[pos++];
            }
            if(ch == 'e'){
                type = 7;
                ch = txt[pos++];
                continue;
            }
            if(!reg)
                cout<<"line"<<line<<":("<<str[type]<<", "<<number<<"."<<word<<")"<<endl;
            else
                cout<<"line"<<line<<":("<<str[type]<<", "<<reg<<number<<"."<<word<<")"<<endl;
            word.clear();
            type = -2;
            number = 0;
            reg = '\0';
        }

        if((ch >= '0')&&(ch <= '9')&&(type==7)){
            word1 += ch;
            ch = txt[pos++];
            while(ch >= '0' && ch <= '9'){
                word1 += ch;
                ch = txt[pos++];
            }
            if(reg&&reg1){
                cout<<"line"<<line<<":("<<str[type]<<", "<<reg<<number<<"."<<word<<"e"<<reg1<<word1<<")"<<endl;
            }
            else if(reg&&!reg1){
                cout<<"line"<<line<<":("<<str[type]<<", "<<reg<<number<<"."<<word<<"e"<<word1<<")"<<endl;
            }
            else if(!reg&&reg1){
                cout<<"line"<<line<<":("<<str[type]<<", "<<number<<"."<<word<<"e"<<reg1<<word1<<")"<<endl;
            }
            else{
                cout<<"line"<<line<<":("<<str[type]<<", "<<number<<"."<<word<<"e"<<word1<<")"<<endl;
            }
            word.clear();
            word1.clear();
            type = -2;
            number = 0;
            reg = '\0';
            reg1 = '\0';
        }


        //��������
        switch(ch){
        //���������
            case '+': {if(txt[pos]=='=') {type = 6;word="+=";cout<<"line"<<line<<":("<<str[type]<<", "<<word<<")"<<endl;ch = txt[pos++];word.clear();break;}
                else{type = -2; cout<<"";ch = txt[pos++]; break;}}
            case '-': {if(txt[pos]>='0'&&txt[pos]<='9'&&type!=7) {reg='-';ch = txt[pos++];break;}
                else if(txt[pos]>='0'&&txt[pos]<='9'&&type==7) {reg1='-';ch = txt[pos++];break;}
                else{type = 6; cout<<"line"<<line<<":("<<str[type]<<", "<<ch<<")"<<endl;ch = txt[pos++]; break;}}
            case '*': type = 6; cout<<"line"<<line<<":("<<str[type]<<", "<<ch<<")"<<endl;ch = txt[pos++]; break;
            case '/': {if(txt[pos]!='*'){type = 6; cout<<"line"<<line<<":("<<str[type]<<", "<<ch<<")"<<endl;ch = txt[pos++]; break;}
                else{while((ch=txt[pos++])!='\n') break;}}
            case '=':
                type = 6;
                if(txt[pos-2]=='+'||txt[pos-1]=='-'){
                    ch = txt[pos++];
                    break;
                }
                else if(txt[pos] == '='){
                    word += ch;
                    ch = txt[pos++];
                    word += ch;
                    ch = txt[pos++];
                    cout<<"line"<<line<<":("<<str[type]<<", "<<word<<")"<<endl;
                    word.clear();
                    break;
                }
                else{
                    cout<<"line"<<line<<":("<<str[type]<<", "<<ch<<")"<<endl;
                    ch = txt[pos++];
                    break;
                }
            case '<':
                type = 6;
                if(txt[pos] == '='){
                    word += ch;
                    ch = txt[pos++];
                    word += ch;
                    ch = txt[pos++];
                    cout<<"line"<<line<<":("<<str[type]<<", "<<word<<")"<<endl;
                    word.clear();
                    break;
                }
                else{
                    cout<<"line"<<line<<":("<<str[type]<<", "<<ch<<")"<<endl;
                    ch = txt[pos++];
                    break;
                }
            case '>':
                type = 6;
                if(txt[pos] == '='){
                    word += ch;
                    ch = txt[pos++];
                    word += ch;
                    ch = txt[pos++];
                    cout<<"line"<<line<<":("<<str[type]<<", "<<word<<")"<<endl;
                    word.clear();
                    break;
                }
                else{
                    cout<<"line"<<line<<":("<<str[type]<<", "<<ch<<")"<<endl;
                    ch = txt[pos++];
                    break;
                }
            case '!':
                type = 6;
                if(txt[pos] == '='){
                    word += ch;
                    ch = txt[pos++];
                    word += ch;
                    ch = txt[pos++];
                    cout<<"line"<<line<<":("<<str[type]<<", "<<word<<")"<<endl;
                    word.clear();
                    break;
                }
                else{
                    cout<<"line"<<line<<":("<<str[type]<<", "<<ch<<")"<<endl;
                    ch = txt[pos++];
                    break;
                }
            case '&':
                type = 6;
                if(txt[pos] == '&'){
                    word += ch;
                    ch = txt[pos++];
                    word += ch;
                    ch = txt[pos++];
                    cout<<"line"<<line<<":("<<str[type]<<", "<<word<<")"<<endl;
                    word.clear();
                    break;
                }
                else{
                    cout<<"line"<<line<<":("<<str[type]<<", "<<ch<<")"<<endl;
                    ch = txt[pos++];
                    break;
                }
            case '|':
                type = 6;
                if(txt[pos] == '|'){
                    word += ch;
                    ch = txt[pos++];
                    word +=ch;
                    ch = txt[pos++];
                    cout<<"line"<<line<<":("<<str[type]<<", "<<word<<")"<<endl;
                    word.clear();
                    break;
                }
                else{
                    cout<<"line"<<line<<":("<<str[type]<<", "<<ch<<")"<<endl;
                    ch = txt[pos++];
                    break;
                }


            //�����ָ���
            case ',': type = 4; cout<<"line"<<line<<":("<<str[type]<<", "<<ch<<")"<<endl; ch = txt[pos++]; break;
            case ';': type = 4; cout<<""; ch = txt[pos++]; break;
            case ':': type = 4; cout<<"line"<<line<<":("<<str[type]<<", "<<ch<<")"<<endl; ch = txt[pos++]; break;

            //�������
            case '(': type = 5; cout<<"line"<<line<<":("<<str[type]<<", \""<<ch<<"\")"<<endl; ch = txt[pos++]; break;
            case ')': type = 5; cout<<"line"<<line<<":("<<str[type]<<", \""<<ch<<"\")"<<endl; ch = txt[pos++];break;
            case '[': type = 5; cout<<"line"<<line<<":("<<str[type]<<", \""<<ch<<"\")"<<endl; ch = txt[pos++];break;
            case ']': type = 5; cout<<"line"<<line<<":("<<str[type]<<", \""<<ch<<"\")"<<endl; ch = txt[pos++];break;
            case '{': type = 5; cout<<"line"<<line<<":("<<str[type]<<", \""<<ch<<"\")"<<endl; ch = txt[pos++];break;
            case '}': type = 5; cout<<"line"<<line<<":("<<str[type]<<", \""<<ch<<"\")"<<endl; ch = txt[pos++];break;
            case '"': type = 5; cout<<"line"<<line<<":("<<str[type]<<", \""<<ch<<"\")"<<endl; ch = txt[pos++];break;
            case '\'':type = 5; cout<<"line"<<line<<":("<<str[type]<<", \""<<ch<<"\")"<<endl; ch = txt[pos++];break;
        }
    }
}


int main()
{
    char c;
    while((c=getchar())!=EOF){
        txt+=c;
    }
    flag1=check();
    if(flag1)   yylex();
    return 0;
}
