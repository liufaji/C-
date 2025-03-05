#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


//---------ϡ��������Ԫ˳��洢�ṹ-------------
#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef struct{
	int i,j;//���±�����±� 
	int e;
}Triple;
typedef struct{
	Triple data[MAXSIZE+1];//data[0]δ�� 
	int mu,nu,tu;//����������������ͷ���Ԫ�ظ��� 
}TSMatrix;
//�㷨5.1 
int TransposeMatrix(TSMatrix *M,TSMatrix *T){
	//������Ԫ��洢��ʾ����ϡ�����M��ת�þ���T�� 
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

//�㷨5.2����ת���㷨
int FastTransposeSMatrix(TSMatrix *M,TSMatrix *T){
	//������Ԫ��˳���洢��ʾ����ϡ�����M��ת�þ���T�� 
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
			//��M��ÿһ�к�����Ԫ�ظ����� 
			++num[M->data[t].j];
		}
		cpot[1]=0;
		//���col���е�һ������Ԫ��b.data�е����� 
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






 
