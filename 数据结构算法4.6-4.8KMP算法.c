#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//定义常量 
#define OK 1
#define ERROR 0
#define OVERFLOW -1


#define MAXSTRING 225
typedef unsigned char SString[MAXSTRING+1];



//算法4.7 
void get_next (SString T,int next[]){
	//求模式串T的next函数值并存入数组next。
	int i=1;
	int j=0;
	next[1]=0;
	while(i<T[0]){
		if(T[i]==T[j]){
			++i;
			++j;
			next[i]=j;
		}else{
			j=next[j];
		}
	}
} 

//算法4.8 
void get_nextval(SString T,int nextval[]){
	//求模式串T的next函数值并存入数组next。
	int i=1;
	int j=0;
	nextval[1]=0;
	while (i<T[0]){
		if(T[i]==T[j]){
			i++;
			j++;
			if(T[i]==T[j]){
				nextval[i]=nextval[j];
			}else{
				nextval[i]=j;
			}
		}else{
			j=nextval[j];
		}
	}
}

//算法4.6 
int Index_KMP(SString *S,SString *T,int pos,int nextval[]){
	int i=pos;
	int j=1;
	while(i<=(*S)[0]&&j<=(*T)[0]){
		if(j==0||S[i]==T[j]){
			i++;
			j++;
		}else{
			j=nextval[j];
		}
		if(j>(*T)[0]) return i-(*T)[0];
		else return 0;
		
	}
}
