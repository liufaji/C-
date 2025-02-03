#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define OK 1
#define ERROR 0
/*typedef int Status;
typedef int ElemType;

*/
//算法2.22
typedef struct {
	float coef;
	int expn;
}term;

typedef struct LNode {
	term data;
	struct LNode* next;
}LNode,*LinkList;


int InitList(LinkList *p){
	*p=(LinkList)malloc(sizeof(LNode));
	if(!*p){
		return 0;
	}
	(*p)->next=NULL;
	return 1;
}
int cmp(term a,term b){
	if(a.expn<b.expn) return -1;
	else if(a.expn>b.expn) return 1;
	else if(a.expn=b.expn) return 0;
}



int LocateElement(LinkList L,term e,LNode **q,int(*compare)(term,term)){
		LNode *per=L;
		LNode *cur=L->next;
		while(cur){
			int cmp_result=compare(cur->data,e);
			if(cmp_result==0){
				*q=per;
				return 1;
			}
			if(cmp_result>0){
				break;
			}
			per=cur;
			cur=cur->next;
			return 0;
		}
}
 
 
int MakeNode(LNode **s,term e){
	*s=(LinkList)malloc(sizeof(LNode));
	if(!(*s)){
		(*s)->data=e;
		(*s)->next=NULL;
	    return 1;
	}else return 0;
	
}
    

int InsAfter(LNode *q,LNode *s){
	if(!q||!s) return 0;
	s->next=q->next;
	q->next=s;
	return 1;
	
}


void CreatPolyn(LinkList *p,int m){
	 InitList(p);
	 LinkList h=*p;
	 term e;
	 (*p)->data.coef=0;
	 (*p)->data.expn=0;
	 int j=0;
	 for(j=1;j<=m;++j){
	 	scanf("%f %d",&e.coef,&e.expn);
	 	LNode* q;
	 	if(LocateElement(*p,e,&q,cmp)==1){
	 		q->next->data.coef+=e.coef;
		 }
		 else {
		 	LNode *s;
		 	if(MakeNode(&s,e)==0){
		 		InsAfter(q,s);
			 }
	     }
	 }
	 
	 
}
int main (){
	LinkList p;
	
}