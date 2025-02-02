#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef struct DuLNode{
	int data;
	struct DuLNode* prior;
	struct DuLNode* next;
}DuLNode,*DuLinkList;

//算法2.18
int ListInsert_DuL(DuLinkList L,int i,int e){
	//在带头结点的双链表循环线性表L中第i个位置之前插入元素e，
	//i的合法值为1<=i<=表长+1
	DuLinkList p=L->next;
	int j=1;
	while(p&&j<i){
		p=p->next;
		j++;
	}
	if(!p||j>i){
		return 0 ;
	}
	DuLinkList s=(DuLinkList)malloc(sizeof(DuLNode));
    if(!s){
    	return 0;
	} 
	s->data=e;
	s->prior=p->prior;
	p->prior->next=s;
	s->next=p;
	p->prior=s;
	return 1;
}

//算法2.18
int ListDelet_DuL(DuLinkList L,int i,int e){
	if (L == NULL) {
        return 0; // 链表为空，返回0
    }
	DuLinkList p=L->next;
	int j=1;
	while(p&&j<i){
		p=p->next;
		j++;
	}
	if(!p||j>i){
		return 0 ;
	}
	if(p->next==NULL){
		e=p->data;
		p->prior->next=NULL;
		free(p);
	}else{
		e=p->data;
		p->prior->next=p->next;
	    p->next->prior=p->prior;
	    free(p);
	}
	return 1;
}
int main(){
	
}