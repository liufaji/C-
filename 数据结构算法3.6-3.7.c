#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

//定义常量 
#define OK 1
#define ERROR 0
#define MAX_WINDOWS 4
#define CLOSE_TIME 480
#define MAX_RAND_ARRIVAL 5
#define MAX_RAND_DURATION 30 
//事件类型定义 
typedef struct {
	int Occurtime ;
	int Ntype;
}Event;
//客户记录定义 
typedef struct {
	int ArrivalTime;
	int Duration;
}CustomerRecord;	
//队列节点定义
typedef struct QNode{
	CustomerRecord data;
	struct QNode *next;
}QNode;
//队列结构定义
typedef struct {
	QNode *front;
	QNode *rear;
	int Length;
}LinkQueue;
//事件链定义
typedef struct ENode{
    Event event;
    struct ENode *next;  
}ENode;

//定义全局变量 
ENode *eventLink=NULL;
LinkQueue queue[MAX_WINDOWS+1];
int TotalTime=0;
int CustomerNum=0;
//函数声明
void OpenForDay();
int cmp(Event a, Event b);
int OrderInsert(Event e);
int ShortestQueue();
void EnQueue(int queueIdx, CustomerRecord customer);
CustomerRecord Dequeue(int queueIdx);
void CustomerArrived(Event e);
void CustomerDeparture(Event e);
void Bank_Simulation();
//初始化 
void OpenForDay(){
	TotalTime=0;
	CustomerNum=0;
	eventLink=NULL;
	int i=0;
	for(i=1;i<=4;i++){
		queue[i].front=queue[i].rear=NULL;
		queue[i].Length=0;
	}
	Event firstEvent={0,0};
	OrderInsert(firstEvent);
}
//比较两个事件发生的时间顺序 
int cmp(Event a,Event b){
	if(a.Occurtime>b.Occurtime) return 1;
	if(a.Occurtime==b.Occurtime) return 0;
	else return -1;
}
//插入事件链 
int OrderInsert(Event e){
	ENode *newNode=(ENode*)malloc(sizeof(ENode));
	if(!newNode) return 0;
	newNode->event=e;
	newNode->next = NULL;
	if(eventLink==NULL){
		eventLink=newNode;
	}else{
		ENode *prev=NULL;
		ENode *current=eventLink;
		while(current!=NULL&&cmp(current->event,e)<0){
			prev=current;
			current=current->next;
		}
		if(prev==NULL){
			newNode->next=eventLink;
			eventLink=newNode;
		}else{
			prev->next=newNode;
			newNode->next=current;
		}
	}
	return 1;
}
int ShortestQueue(){
	int minLen=queue[1].Length;
	int i=0;
	int minIdx=1;
	for(i=2;i<=MAX_WINDOWS;i++){
		if(queue[i].Length<minLen){
			minLen=queue[i].Length;
			minIdx=i;
		}
	}
	return minIdx;
}
//插入队列
void EnQueue(int queueIdx,CustomerRecord customer){
	QNode *newNode=(QNode*)malloc(sizeof(QNode));
	newNode->data=customer;
	newNode->next=NULL;
	if(queue[queueIdx].front==NULL){
		queue[queueIdx].front=queue[queueIdx].rear=newNode;
	}else{
		queue[queueIdx].rear->next=newNode;
		queue[queueIdx].rear=newNode;
	}
	queue[queueIdx].Length++;
} 
//处理客户到达事件 
void CustomerArrived(Event e){
	CustomerNum++;
	int intertime = rand() % MAX_RAND_ARRIVAL + 1;
    int duration = rand() % MAX_RAND_DURATION + 1;
    //生成下一个客户到达事件
	if(intertime+e.Occurtime<CLOSE_TIME){
		Event NextArrival={intertime+e.Occurtime,0};
		OrderInsert(NextArrival);
	} 
	//将当前客户加入最短队列
	int queueIdx=ShortestQueue();
	CustomerRecord customer={e.Occurtime,duration};
	EnQueue(queueIdx,customer);
	//如果队伍之前为空，则生成离开事件
	if(queue[queueIdx].Length==1){
		Event departure={e.Occurtime+duration,queueIdx};
		OrderInsert(departure);
	} 
} 
//出队操作 
CustomerRecord Dequeue(int queueIdx){
	QNode *temp=queue[queueIdx].front;
	CustomerRecord data=temp->data;
	queue[queueIdx].front=queue[queueIdx].front->next;
	if(queue[queueIdx].front==NULL){
		queue[queueIdx].rear=NULL;
	}
	queue[queueIdx].Length--;
	return data;
} 
//处理用户离开事件
void CustomerDeparture(Event e){
	int queueIdx=e.Ntype;
	CustomerRecord customer=Dequeue(queueIdx);
	TotalTime+=e.Occurtime-customer.ArrivalTime;
	//如果队列不为空，处理下一个客户
	if(queue[queueIdx].Length>0){
		CustomerRecord nextCustomer=queue[queueIdx].front->data;
		Event nextDeparture={e.Occurtime+nextCustomer.Duration,queueIdx};
		OrderInsert(nextDeparture);
	} 
}
//银行模拟主函数 
void  Bank_Simulation(){
	srand(time(NULL));
	OpenForDay();
	
	while(eventLink!=NULL){
		ENode *currentevent=eventLink;
		eventLink=eventLink->next;
		if(currentevent->event.Ntype==0){
			CustomerArrived(currentevent->event);
		}else{
			CustomerDeparture(currentevent->event);
		}
		free(currentevent);
	} 
	//输出结果
	if(CustomerNum>0){
		printf("总客户数: %d\n", CustomerNum);
        printf("总逗留时间: %d 分钟\n", TotalTime);
        printf("平均逗留时间: %.2f 分钟\n", (float)TotalTime / CustomerNum);
	}else {
        printf("没有客户办理业务。\n");
    } 
}

 
int main(){
	Bank_Simulation();
	return 0;
}
