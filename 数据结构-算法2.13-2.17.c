#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define MAXSIZE 15
#define ElemType int 
typedef struct{
	int data;
	int cur;
}component,SLinkList[MAXSIZE];
//算法2.13
int LocateElem_SL(SLinkList S,ElemType e){
	SLinkList s;
	int i=s[0].cur;
	while(i&&s[i].data!=e){
		i=s[i].cur;
	}
	return i;
}

//算法2.14
void InitSpace_SL(SLinkList* space){
	int i=0;
	for(i=0;i<MAXSIZE-1;++i){
		(*space)[i].cur=i+1;
	}
	(*space)[MAXSIZE-1].cur=0;
}

//算法2.15
int Malloc_SL(SLinkList* space){
	int i=(*space)[0].cur;
    if((*space)[0].cur){
    	(*space)[i].cur;
	}
	return i;	
}

//算法2.16
void Free_SL(SLinkList *space,int k){
	(*space)[k].cur=(*space)[0].cur;
	(*space)[0].cur=k;
}

    
int main(){
	SLinkList space;
	InitSpace_SL(&space);
    int m=0,n=0;
    printf("请输入A，B集合元素个数");
	scanf("%d %d",&m,&n);
	int j=0;
	int s=Malloc_SL(&space);
	int r=s;
	for(j=1;j<=m;++j){
		int i=Malloc_SL(&space);
		scanf("%d",&space[i].data);
		space[r].cur=i;
		r=i;
	}
	space[r].cur=0;//最后一个节点
	for(j=1;j<=n;++j){
		int b=0;
		scanf("%d",&b);
		int p=s;
		int k=space[s].cur;
		while(k!=space[r].cur&&space[k].data!=b){
			p=k;
			k=space[k].cur;
	    }
	    if(k==space[r].cur){
		    int i=Malloc_SL(&space);
		    space[i].data=b;
	        space[i].cur=space[r].cur;
	        space[r].cur=i;
	    }else{
	    	space[p].cur=space[k].cur;
	    	Free_SL(&space,k);
	    	if(r==k){
	    		r=p;
			}
		}
		
	}
	
	
}