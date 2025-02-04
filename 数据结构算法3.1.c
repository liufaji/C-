#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define STACK_INIT_SIZE 20
#define STACKINCREAMENT 10
typedef struct {
	int *base;
	int *top;
	int stacksize;
}SqStack;

int InitStack(SqStack *S){
	S->base=(int*)malloc(STACK_INIT_SIZE*sizeof(int));
	if(!(S->base)) return 0;
	S->top=S->base;
	S->stacksize=STACK_INIT_SIZE;
	return 1;
}


int Push(SqStack *S,int e){
	if((S->top-S->base)>=S->stacksize){
		S->base=(int*)realloc(S->base,(S->stacksize+STACKINCREAMENT)*sizeof(int));
		if(!(S->base)) return 0;
	    S->top=S->base+S->stacksize;
	    S->stacksize+=STACKINCREAMENT;
	}
    *S->top++=e;
    return 1;
}

int Pop(SqStack *S){
	if(S->base==S->top) return 0;
	int e=*--S->top;
	return e;
}


int StackEmpty(SqStack *S){
	if(S->top==S->base) return 0;
	return 1;
}
//算法3.1
int conversion(SqStack *S){
	if(!InitStack(S)) return 0;
	printf("请输入十进制数");
	int A=0;
	scanf("%d",&A);
	while(A){
		Push(S,A%8);
		A=A/8;
	}
	while(StackEmpty(S)){
		int e=Pop(S);
		printf("%d",e);
	}
	return 1;
}
int main(){
	SqStack S;
	conversion(&S);
}