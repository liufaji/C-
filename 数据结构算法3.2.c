#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define STACK_INIT_SIZE 20
#define STACKINCREAMENT 10
typedef struct {
	char *base;
	char *top;
	int stacksize;
}SqStack;

int InitStack(SqStack *S){
	S->base=(char*)malloc(STACK_INIT_SIZE*sizeof(char));
	if(!(S->base)) return 0;
	S->top=S->base;
	S->stacksize=STACK_INIT_SIZE;
	return 1;
}


int Push(SqStack *S,char e){
	if((S->top-S->base)>=S->stacksize){
		S->base=(char*)realloc(S->base,(S->stacksize+STACKINCREAMENT)*sizeof(char));
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


void ClearStack(SqStack *S){
	if(S->stacksize>STACK_INIT_SIZE){
		S->base=(char*)realloc(S->base,(STACK_INIT_SIZE)*sizeof(char));
	}
	S->top=S->base;
}
//�㷨3.1
int conversion(SqStack *S){
	if(!InitStack(S)) return 0;
	printf("������ʮ������"); 
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

//�㷨3.2
//�����ַ�ջS�����ն˽���һ�в����������ù��̵������� 
void LineEdit(SqStack *S){
	InitStack(S);
	char ch=getchar();
	while(ch!=EOF){
		while(ch!=EOF&&ch!='\n'){
			switch(ch){
				case'#':
					Pop(S);
					break;
				case'@':
					ClearStack(S);
					break;
				default:
					Push(S,ch);
			}
			ch=getchar();	
		}
		//����ջ�׵�ջ����ջ���ַ����������ù��̵������� 
		ClearStack(S);
		if(ch!=EOF) ch=getchar();
		
	}
} 
int main(){
	SqStack S;
	conversion(&S);
}



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

