#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

//���峣�� 
#define OK 1
#define ERROR 0
#define MAX_WINDOWS 4
#define CLOSE_TIME 480
#define MAX_RAND_ARRIVAL 5
#define MAX_RAND_DURATION 30 
//�¼����Ͷ��� 
typedef struct {
	int Occurtime ;
	int Ntype;
}Event;
//�ͻ���¼���� 
typedef struct {
	int ArrivalTime;
	int Duration;
}CustomerRecord;	
//���нڵ㶨��
typedef struct QNode{
	CustomerRecord data;
	struct QNode *next;
}QNode;
//���нṹ����
typedef struct {
	QNode *front;
	QNode *rear;
	int Length;
}LinkQueue;
//�¼�������
typedef struct ENode{
    Event event;
    struct ENode *next;  
}ENode;

//����ȫ�ֱ��� 
ENode *eventLink=NULL;
LinkQueue queue[MAX_WINDOWS+1];
int TotalTime=0;
int CustomerNum=0;
//��������
void OpenForDay();
int cmp(Event a, Event b);
int OrderInsert(Event e);
int ShortestQueue();
void EnQueue(int queueIdx, CustomerRecord customer);
CustomerRecord Dequeue(int queueIdx);
void CustomerArrived(Event e);
void CustomerDeparture(Event e);
void Bank_Simulation();
//��ʼ�� 
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
//�Ƚ������¼�������ʱ��˳�� 
int cmp(Event a,Event b){
	if(a.Occurtime>b.Occurtime) return 1;
	if(a.Occurtime==b.Occurtime) return 0;
	else return -1;
}
//�����¼��� 
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
//�������
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
//����ͻ������¼� 
void CustomerArrived(Event e){
	CustomerNum++;
	int intertime = rand() % MAX_RAND_ARRIVAL + 1;
    int duration = rand() % MAX_RAND_DURATION + 1;
    //������һ���ͻ������¼�
	if(intertime+e.Occurtime<CLOSE_TIME){
		Event NextArrival={intertime+e.Occurtime,0};
		OrderInsert(NextArrival);
	} 
	//����ǰ�ͻ�������̶���
	int queueIdx=ShortestQueue();
	CustomerRecord customer={e.Occurtime,duration};
	EnQueue(queueIdx,customer);
	//�������֮ǰΪ�գ��������뿪�¼�
	if(queue[queueIdx].Length==1){
		Event departure={e.Occurtime+duration,queueIdx};
		OrderInsert(departure);
	} 
} 
//���Ӳ��� 
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
//�����û��뿪�¼�
void CustomerDeparture(Event e){
	int queueIdx=e.Ntype;
	CustomerRecord customer=Dequeue(queueIdx);
	TotalTime+=e.Occurtime-customer.ArrivalTime;
	//������в�Ϊ�գ�������һ���ͻ�
	if(queue[queueIdx].Length>0){
		CustomerRecord nextCustomer=queue[queueIdx].front->data;
		Event nextDeparture={e.Occurtime+nextCustomer.Duration,queueIdx};
		OrderInsert(nextDeparture);
	} 
}
//����ģ�������� 
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
	//������
	if(CustomerNum>0){
		printf("�ܿͻ���: %d\n", CustomerNum);
        printf("�ܶ���ʱ��: %d ����\n", TotalTime);
        printf("ƽ������ʱ��: %.2f ����\n", (float)TotalTime / CustomerNum);
	}else {
        printf("û�пͻ�����ҵ��\n");
    } 
}

 
int main(){
	Bank_Simulation();
	return 0;
}
