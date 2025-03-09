#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -1
//--------------ϡ������ʮ������洢��ʽ------------ 
typedef struct OLNode{
	int i,j,e;//�÷���Ԫ���к����±� 
	struct OLNode *right,*down;//�÷���Ԫ�����б������ĵĺ������ 
}OLNode,*OLink; 
typedef struct{
	OLink *rhead,*chead;//�к�������ͷָ��������ַ��CreateSMatrix���䡣 
	int mu,nu,tu;//ϡ����������������ͷ���Ԫ���� 
}CrossList; 

int CreatSMatrix_OL(CrossList *M){
	//����ϡ�����M������ʮ������洢
	if(M) free(M);
	
	scanf("%d,%d,%d",&M->mu,&M->nu,&M->tu); 
	if(!(M->rhead=(OLink*)malloc((M->mu+1)*sizeof(OLink)))) exit(OVERFLOW);
	if(!(M->chead=(OLink*)malloc((M->nu+1)*sizeof(OLink)))) exit(OVERFLOW);
	int i=0,j=0,e=0;
	for(scanf("%d,%d,%d",&i,&j,&e);i!=0;scanf("%d,%d,%d",&i,&j,&e)){
		OLNode *p=NULL;
		if(!(p=(OLNode*)malloc(sizeof(OLNode)))) exit (OVERFLOW);
		p->i=i;
		p->j=j;
		p->e=e;
		p->down=NULL;
		p->right=NULL;
		if(M->rhead[i]==NULL||M->rhead[i]->j>j){
			p->right=M->rhead[i];
			M->rhead[i]=p;
		}else{
			OLNode *q=M->rhead[i];
			for(q;q->right&&q->right->j<j;q=q->right);
			p->right=q->right;
			q->right=p;
		}
		if(M->chead[j]==NULL||M->chead[j]->i>i){
			p->down=M->chead[j];
			M->chead[j]=p;
		}else{
			OLNode *q=M->chead[j];
			for(q=M->chead[j];q->down&&q->down->i<i;q=q->down);
			p->down=q->down;
			q->down=p;
		}
	}
	return OK;
}



