#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct LNode{
	int date;
	struct LNode* next;
}LNode;

//算法2.8
int GetElem_L(LNode *L,int i,int e){
	LNode* p=L->next;
	int j=1;
	while(p&&j<i){
		p=p->next;
		++j;
    }
	if(!p||j>i){
		return -2;
	}
	
}


//算法2.9
int ListInsert_L(LNode* L,int i,int e){
	LNode* p=L->next;
	int j=1;
	while(p&&j<i-1){
		p=p->next;
		++j;
	}
	if(!p||i<j){
		return -2;
	}
	LNode* pe=(LNode*)malloc(sizeof(LNode));
	pe->date=e;
	pe->next=p->next;
	p->next=pe;
	return e;
}

//算法2.10
int ListDelet_L(LNode* L,int i,int e){
	int j=1;
	LNode* p=L->next;
	while(p&&j<i-1){
		p=p->next;
		++j;
	}
	if(!p||i<j){
		return -2;
	}
	LNode* q=p->next;
	p->next=q->next;
	e=q->date;
	free(q);
	return e;
}

//算法2.11
void CreateList_L(LNode *L,int n){
	L=(LNode*)malloc(sizeof(LNode));
	int i=1;
	for(i=1;i<n;i++){
	    LNode* p=(LNode*)malloc(sizeof(LNode));
	    scanf("%d",p->date);
	    p->next=L->next;
	    L->next=p;
    }
}

//算法2.12
void MergeList_L(LNode *La,LNode*Lb,LNode *Lc){
	LNode* pa=La->next;
	LNode* pb=Lb->next;
	LNode* pc=Lc;
	while(pa&&pb){
		if(pa->date>=pb->date){
			pc->next=pb;
			pc=pb;
			pb=pb->next;
		}else{
			pc->next=pa;
			pc=pa;
			pa=pa->next;
		}
	}
	pc->next=pa?pa:pb;
	free(La);
	free(Lb);
}

int man(){
	LNode headnode;
	LNode* L=&headnode;
	
	
}