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
	//����һ����ѭ������ 
	Q->base=(int*)malloc(MAX_SIZE*sizeof(int));
	if(!Q->base) return ERROR;
	Q->front=Q->rear=0;
	return OK;
}

int QueueLength(SqQueue *Q){
	//f����Q��Ԫ�ظ����������г��� 
	return(Q->front-Q->rear+MAX_SIZE)%MAX_SIZE;
} 

int EnQueue(SqQueue *Q,int e){
	//����Ԫ��eΪQ���µĶ�βԪ��
	if((Q->rear+1)%MAX_SIZE==Q->front) return ERROR;
	Q->base[Q->rear]=e;
	Q->rear=(Q->rear+1)%MAX_SIZE;
	return OK;
}

int DeQueue(SqQueue *Q,int e){
	//�����в�Ϊ�գ���ɾ��Q�Ķ�ͷԪ�أ���e���ء� 
	if(Q->front==Q->rear) return ERROR;
	e=Q->base[Q->front];
	Q->front=(Q->front+1)%MAX_SIZE;
    return OK; 
}
