#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//定义常量 
#define OK 1
#define ERROR 0
#define MAXSTRING 225
typedef unsigned char SString[MAXSTRING+1];
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
 
