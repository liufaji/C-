#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define OK 1
#define ERROR 0
typedef int Status;
typedef int ElemType;

typedef struct LNode{
	int data;
	struct LNode* next;
}*Link,*Position;

typedef struct{
	Link head,tail;
	int len;
}LinkList;


Status Locatepos(LinkList *L,int i,Link *p){
	int j=1;
	*p=L->head;
	while(*p&&j<i){
		*p=(*p)->next;
	}
	if(!(*p)||j>i){
		return ERROR;
	}else return OK;
}

Status InsFirst(Link h,Link s){
	s->next=h->next;
	h->next=s;
	return OK;
}

Status MakeNode(Link *p,ElemType e){
	*p=(Link)malloc(sizeof(struct LNode));
	if(!*p)return ERROR;
	(*p)->data=e;
	(*p)->next=NULL;
	return OK;
}

//算法2.20
Status ListInsert_L(LinkList *L,int i,ElemType e){
	Link p,s;
	if(!(Locatepos(L,i-1,&p))){
		return ERROR;
	}
	if(!MakeNode(&s,e)){
		return ERROR;
	}
	InsFirst(p,s);
	L->len++;
	if(p==L->tail) L->tail=s;
	return OK;
}



int main(){
	
}