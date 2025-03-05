#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


//---------稀疏矩阵的三元顺序存储结构-------------
#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef struct{
	int i,j;//行下表和列下标 
	int e;
}Triple;
typedef struct{
	Triple data[MAXSIZE+1];//data[0]未用 
	int mu,nu,tu;//矩阵的行数和列数和非零元素个数 
}TSMatrix;
//算法5.1 
int TransposeMatrix(TSMatrix *M,TSMatrix *T){
	//采用三元组存储表示，求稀疏矩阵M的转置矩阵T。 
	T->mu=M->nu;
	T->nu=M->mu;
	T->tu=M->tu;
	if(T->tu){
		int q=1;
		int col=0;
		for(col=1;col<=M->nu;col++){
			int p=1;
			for(p=1;p<=M->tu;p++){
				if(M->data[p].j==col){
					T->data[q].i=M->data[p].j;
					T->data[q].j=M->data[p].i;
					T->data[q].e=M->data[p].e;
					++q;
				}
			}
		}
	}
	return OK;
}

//算法5.2快速转置算法
int FastTransposeSMatrix(TSMatrix *M,TSMatrix *T){
	//采用三元组顺序表存储表示，求稀疏矩阵M的转置矩阵T。 
	T->mu=M->nu;
	T->nu=M->mu;
	T->tu=M->tu;
	if(T->tu){
		int num[M->nu+1];
		int cpot[M->nu+1];
		int col=1;
		for(col;col<=M->nu;col++){
			num[col]=0;
		}
		int t=1;
		for(t;t<=M->tu;t++){
			//求M的每一列含非零元素个数。 
			++num[M->data[t].j];
		}
		cpot[1]=0;
		//求第col列中第一个非零元在b.data中的序列 
		for(col=2;col<=M->nu;col++){
			cpot[col]=cpot[col-1]+num[col-1];
		}
		int p=1;
		int q=0;
		for(p;p<=M->tu;p++){
			col=M->data[p].j;
			q=cpot[col];
			T->data[q].i=M->data[p].j;
			T->data[q].j=M->data[p].i;
			T->data[q].e=M->data[p].e;
			++cpot[col]; 
		}
	}
	return OK;
}






 
