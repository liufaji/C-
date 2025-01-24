#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*#define MAX_SIZEOF 100//定义线性表的最大容量
//定义线性表结构体
typedef struct {
	int list[10];
	int length;
}SepList;
//初始化线性表
void InitList (SepList*L){
	L->length=0;
}
//插入元素
int ListInsert(SepList*L,int i,int e){
	if(i<1||i>L->length+1){
		printf("插入位置无效");
		return 0;
	}
	if(i>MAX_SIZEOF){
		printf("超出列表最大范围");
		return 0;
	}
	if(i>=1&&i<=L->length){//插入元素向后调一位
		int a=0;
		for(a=L->length;a>=i;a--){
			L->list[a+1]=L->list[a];
			L->list[i]=e;
	        L->length++;
	        return 1;
		}
	}
	if(i==L->length+1){
		L->list[L->length+1]=e;
		L->length++;
		return 1;
	}
	
}
//删除元素
int DeletList(SepList*L,int i){
	if(i<1||i>L->length){
		printf("删除无效");
		return 0;
	}
	if(i>=1&&i<=L->length){
		int a=0;
		for(a=i;a<=L->length-1;a++){
			L->list[a]=L->list[a+1];
	    }
		L->length--;
	}return 1;
	
}
//打印线性表
int printList(SepList*L){
	int i=0;
	for(i=1;i<=L->length;i++){
		printf("%d\n",L->list[i]);
		     	                                                                       
	}
	return 1;
}

int main (){
    SepList L;//创建链表
    InitList(&L);
    ListInsert(&L,1,10);
    ListInsert(&L,2,20);
    ListInsert(&L,3,30);
    ListInsert(&L,4,40);
    ListInsert(&L,5,50);
    ListInsert(&L,6,60);
    ListInsert(&L,7,70);
    
    
    DeletList(&L,3);
    DeletList(&L,5);
    printList(&L);
}

*/

#define LIST_INIT_SIZEOF 5
#define LISTINCREMENT 2


typedef struct {
    int* elem;
	int length;
	int listsizeof;
}SpList;


int InitList_Sp(SpList*pL){
	pL->elem=(int*)malloc(LIST_INIT_SIZEOF*sizeof(int));
	if(!(pL->elem)){
		exit(-2);
	}
	pL->length=0;
	pL->listsizeof=LIST_INIT_SIZEOF;
	return 1;
}


int InsertList_Sp(SpList* pL,int i,int e){
	if(i<1||i>pL->length+1){
		return 0;	
	}
	int*newbase;
	if(i>=pL->listsizeof){
		newbase=(int*)realloc(pL->elem,(pL->length+LISTINCREMENT)*sizeof(int));
		if(!newbase){
			exit(-2);
			pL->elem=newbase;
			pL->listsizeof+=LISTINCREMENT;
			
		}
		
	}
	int* pi=newbase;
	int p=0;
	for(p=pL->length;p>=i;p--){
	    pi[p+1]=pi[p];
	}
	pi[i]=e;
	pL->length++;
	return 1;
}


int DeleteList_Sp(SpList* pL,int i){
	if(i<1||i>pL->length){
		return 0;
	}
	int* newbase;
	int* pi=newbase;
	int q=0;
	for(q=i+1;q<=pL->length;q++){
		pi[q-1]=pi[q];
	}
	--pL->length;
	return 1;
}
int main(){
    SpList L;
    InitList_Sp(&L);
    //InsertList_Sp(&L,i,e);
    //DeleteList_Sp(&L;i,e);
    
}
