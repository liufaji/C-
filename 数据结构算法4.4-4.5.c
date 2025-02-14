#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//定义常量 
#define OK 1
#define ERROR 0
#define OVERFLOW -1


#define MAXSTRING 225
typedef unsigned char SString[MAXSTRING+1];
/*
//算法4.2 
int Concat(SString (*T),SString *S1,SString (*S2)){
	if((*S1)[0]+((*S2))[0]<=((*T))[0]){
	    int i=0;
	    for(i=1;i<=(*S1)[0];i++){
	    	(*T)[i]=(*S1)[i]; 
		}
		for(i=1;i<=((*S2))[0];++i){
			(*T)[(*S1)[0]+i]=((*S2))[i];
		}
		(*T)[0]=(*S1)[0]+(*S2)[0];
		return 1;
	}else if((*S1)[0]<(*T)[0]){
		int i=0;
	    for(i=1;i<=(*S1)[0];i++){
	    	(*T)[i]=(*S1)[i]; 
		}
		for(i=1;i<=(*T)[0];++i){
			(*T)[(*S1)[0]+i]=(*S2)[i];
		}return 0;
		
	}else {
		int i=0;
	    for(i=1;i<=(*T)[0];i++){
	    	(*T)[i]=(*S1)[i]; 
		}return 0;
	}
}
//算法4.3
int SubString(SString *Sub,SString *S,int pos,int len){
	if(pos<0||pos>(*S)[0]||len<0||len>(*S)[0]-pos+1){
		return 0;
	}
	int i=0;
	for(i=pos;i<+pos+len;i++){
		(*Sub)[i-pos+1]=(*S)[i];
		}
		(*Sub)[0]=len;
		return 1;
	}
*/

//算法4.4
typedef struct{
	char *ch;
	int Length;
}HString; 
int StringInsret(HString *S,int pos,HString *T){
	if(pos<1||pos>S->Length+1) return ERROR;
	
		if(T->Length){
			if(!(S->ch=(char*)realloc(S->ch,(S->Length+T->Length)*sizeof(int))));
		}
		int i=0;
		for(i=S->Length-1;i>=pos-1;i--){
			S->ch[i+T->Length]=S->ch[i];
		}
		for(i=pos;i<pos-1+T->Length;i++){
			S->ch[i]=T->ch[i+1-pos];
		}
		S->Length+=T->Length;
		return OK;
}
int StringAssign(HString *T,char *chars){
	if(T->ch) free(T->ch),T->ch=NULL;
	int i=0;
	char *c=NULL;
	for(i=0,c=chars;*c;i++,c++);
	if(!(T->ch=(char*)malloc(i*sizeof(char)))) exit(OVERFLOW);
	T->Length=i;
	for(i=0;i<=T->Length-1;i++){
		(T->ch)[i]=(c)[i];
	}
	return OK;
}
int StrLength(HString *S){
	return S->Length;
}
int StrCompare(HString *S,HString *T){
	int i=0;
	for(i=0;i<S->Length&&i<T->Length;++i){
		if(S->ch[i]!=T->ch[i]) return S->ch[i]-T->ch[i];
	}
	return S->Length-T->Length;
}
int ClearString(HString *S){
	if(S->ch){
		free(S->ch);
		S->ch=NULL;
		S->Length=0;
	}
	return OK;
}
int Concat (HString *T,HString *S1,HString *S2){
	if(T->ch){
		free(T->ch);
		T->ch=NULL;
	}
	if(!(T->ch=(char*)malloc((S1->Length+S2->Length)*sizeof(char)))) exit(OVERFLOW);
	strcpy(T->ch,S1->ch);
	strcat(T->ch,S2->ch);
	return OK;
} 
int SubString (HString *Sub,HString *S,int pos,int len){
	if(pos<0||pos>S->Length||len<0||S->Length-pos+1) exit(OVERFLOW);
	if(Sub->ch){
		free(Sub->ch);
		
	}
	if(!len){
		Sub->ch=NULL;
		Sub->Length=0;
		return 1;
	}else{
		
	    if(!(Sub->ch=(char*)malloc(len*sizeof(char)))) exit (OVERFLOW);
	    int i=0;
	    for(i=pos;i<pos+len;i++){
		    Sub->ch[i-pos]=S->ch[i];
		    }
		    S->Length=len;
		    return 1;
	}
}
int Index (SString *S,SString *T,int pos){
	int i=pos;
	int j=1;
	while (i<=(*S)[0]&&j<=(*T)[0]){
		if((*S)[i]==(*T)[j]){
			++i;
			++j;
		}else{
			i=i-(j-1)+1;
			j=1;
		}
    }
		if(j>(*T[0])) return i-T[0];
		else return 0;
	
}
