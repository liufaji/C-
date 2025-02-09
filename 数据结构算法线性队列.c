#include <stdio.h>
#include <stdlib.h>
//链式队列


 
#define OVERFLOW -2
#define INFEASBLE -1
#define ERROR 0
#define OK 1
typedef struct QNode {
	int data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

int InitQueue(LinkQueue *Q){
	//创造一个队列Q 
    Q->front=Q->rear=(QueuePtr)malloc(sizeof(QNode));
    if(!Q->front){
    	exit(OVERFLOW);
	}
	Q->front->next=NULL;
	return OK;
}

int DestoryQueue(LinkQueue *Q){
    //销毁队列Q 
	while(Q->front){
		Q->rear=Q->front->next;
		free(Q->front);
		Q->front=Q->rear;
	} 
	return OK;
}

int EnQueue(LinkQueue *Q,int e){
	QueuePtr 	p=(QNode*)malloc(sizeof(QNode));
    p->data=e;
    p->next=NULL;
    Q->rear->next=p;
    Q->rear=p;
	return OK; 
} 

int DeQueue(LinkQueue *Q,int e){
	if(Q->front==Q->rear){
		return ERROR;
	}
	QueuePtr p=Q->front->next;
	e=p->data;
	Q->front->next=p->next;
	if(Q->rear==p) Q->rear=Q->front;
	free(p);
	return OK;
}

int main(){
	LinkQueue Q;
	InitQueue(&Q);
}
