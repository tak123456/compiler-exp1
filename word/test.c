int a,b,c;//单行注释
float m,n;
char c1='a';//增加char类型
char c2='b
char ch[10];//增加数组的定义
string str1='abab';
string str='abc 
int fibo(int a)
{/*注释部分自动去掉*/
	int i;
	if(a == 1 || a == 2){
	  return 1;
        }
	for(i<15){//增加了for语句循环
          i++;
	}
	return fibo(a-1)+fibo(a-2);
}
int main()//main函数
{
	/*多行
	注释*/
	int m,n,i;
	char c;
	float ar[20];
	m=read();
	i=1;
	i++;
	--i;//加了自增和自减
	m+=i+15;//加了复合赋值运算
	while(i <= m){
		n=fibo(i);
		write(n);
		i=i+1;
	}
	return 1;
}

