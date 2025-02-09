#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAX_SIZE 10
typedef struct {
	int *base;
	int front;
	int rear;
}SqQueue;

int InitQueue(SqQueue *Q){
	//构造一个空循环队列 
	Q->base=(int*)malloc(MAX_SIZE*sizeof(int));
	if(!Q->base) return ERROR;
	Q->front=Q->rear=0;
	return OK;
}

int QueueLength(SqQueue *Q){
	//f返回Q的元素个数，即队列长度 
	return(Q->front-Q->rear+MAX_SIZE)%MAX_SIZE;
} 

int EnQueue(SqQueue *Q,int e){
	//插入元素e为Q的新的队尾元素
	if((Q->rear+1)%MAX_SIZE==Q->front) return ERROR;
	Q->base[Q->rear]=e;
	Q->rear=(Q->rear+1)%MAX_SIZE;
	return OK;
}

int DeQueue(SqQueue *Q,int e){
	//若队列不为空，则删除Q的队头元素，用e返回。 
	if(Q->front==Q->rear) return ERROR;
	e=Q->base[Q->front];
	Q->front=(Q->front+1)%MAX_SIZE;
    return OK; 
}
