#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


//---------5.2数组的顺序存储表示-------------
#define MAX_ARRAY_DIM 8
#define ERROR 0
#define OVERFLOW -1
#define OK 1


typedef struct {
	int *base;
	int dim;
	int *bounds;
	int *constants;
}Array; 
//初始化数组 
void InitArray(Array *a,int dim,int *bounds){
	a->dim=dim;
	a->bounds=bounds;
	int i=0;
	//计算数组大小并分配内存 
	int total_size=1;
	for(i=0;i<a->dim;++i){
		total_size*=a->bounds[i];
	}
	a->base=(int*)malloc(total_size*sizeof(int));
	//计算constants
	 a->constants=(int*)malloc(a->dim*sizeof(int));
	 i=0;
	 a->constants[a->dim-1]=1;
	 for(i=a->dim-2;i>=0;--i){
	 	a->constants[i]=a->bounds[i+1]*a->constants[i+1];
	 }
	 //初始化数组元素
	 i=0;
	 for(i=0;i<total_size;i++){
	 	a->base[i]=i+1;
	 }
}

int DestroyArray(Array *A){
	//销毁数组 
	if(!A->base) return ERROR;
	free(A->base);
	A->base=NULL;
	if(!A->bounds) return ERROR;
	free(A->bounds);
	A->bounds=NULL;
	if(!A->constants) return ERROR;
	free(A->constants);
	A->constants=NULL;
	return OK;
} 
int Locate(Array *A,va_list aq,int *off){
	*off=0;
	int i=0;
	for(i=0;i<A->dim;i++){
		int ind=va_arg(aq,int);
		if(ind<0||ind>=A->bounds[i]) return OVERFLOW;
		*(off)+=A->constants[i]*ind;
	} 
	return OK;
}
int Value(Array *A,int *e,...){
	//A是n维数组，e为元素变量，随后是n个下标值。
	//若个下标不超界，则e赋值为所指定的值，rerturn OK 
	va_list aq;
	va_start(aq,e);
	int off=0;
	int result=Locate(A,aq,&off);
	if(result<=0) return result;
	*e=*(A->base+off);
	va_end(aq);
	return OK;
}

int Assign(Array *A,int e,...){
	//A是n维数组，e为元素变量，随后是n个下标值。
	//若下标不超界，则将e的值赋值给所指定的A的元素，并返回OK。 
	va_list aq;
	va_start(aq,e);
	int off=0;
	int result=Locate(A,aq,&off);
	if(result<=0){
		va_end(aq);
		return result;
	}
	A->base[off]=e;
	va_end(aq);
	return OK;
}
int main(){
     //定义4维数组的大小 
     int dim=4;
     int bounds[]={2,3,4,5};
     //初始化数组 
     Array A;
     int e;
     InitArray(&A,dim,bounds);
     //访问数组元素
     printf("输入值为"); 
     scanf("%d",&e);
     Assign(&A,e,2,2,3,4);
     Value(&A,&e,2,2,3,4);
     printf("值为%d",e);
}
