#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//���峣�� 
#define OK 1
#define ERROR 0
#define String char*
int StrLength(String e){
	String p=e;
    int i=strlen(p);
	return i;
}
int SubString(String Sub,String S,int i,int m){
	if(!S) return 0;
	if(i<0||m<0||i>StrLength(S)||m>StrLength(S)-i) return 0;
	strncpy(Sub,S+i,m);
	Sub[m]=0;
	return 1;
}



//�㷨4.1 
int Index(String S,String T,int pos){
	if(pos>0){
		int n=StrLength(S);
		int m=StrLength(T);
		int i=0;
		while(i<n-m+1){
			char Sub[m];
			SubString(Sub,S,i,m);
			if(strcmp(Sub,T)!=0) ++i;
			else return i;
		}
		
	} 
	return 0;
}
int main(){
	String S = "Hello, World!";
    String T = "World";
    int pos = Index(S, T, 1);
    if (pos > 0) {
        printf("�Ӵ� \"%s\" �������е�λ��: %d\n", T, pos); // ��� 8
    } else {
        printf("δ�ҵ��Ӵ� \"%s\"\n", T);
    }
    return 0;
}

