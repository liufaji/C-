#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define OK 1
#define ERROR 0
#define MAXSIZE 1000
#define MAXRC 100

typedef struct{
    int i,j;
	int v;	
}Triple;

typedef struct{
	Triple data[MAXSIZE+1];
	int rpos[MAXRC+1];
	int mu,nu,tu;
}RLSMatrix;

void InitMatrix(RLSMatrix *M,int mu,int nu,int tu){
	M->mu=mu;
	M->nu=nu;
	M->tu=tu;
	int i=0;
	for(i=1;i<=mu;++i){
		M->rpos[i]=0;
	}
}

//æÿ’Ûœ‡≥À
int MultSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix *Q){
	if(M.nu!=N.mu) return ERROR;
	Q->mu=M.mu;
	Q->nu=N.nu;
	Q->tu=0;
	
	if(M.tu*N.tu!=0){
		int ctemp[MAXRC+1];
		int arow=1;
	    for(arow;arow<=M.mu;++arow){
			int col=0;
		    for(col=1;col<=N.nu;col++){
		    	ctemp[col]=0;
			}
			Q->rpos[arow]=Q->tu+1;
		    int tp=(arow<M.mu)?M.rpos[arow+1]:M.tu+1;
		    int p=0;
		    for(p=M.rpos[arow];p<tp;p++){
			    int brow=M.data[p].j;
			    int t=(brow<N.nu)?N.rpos[brow+1]:N.tu;
			    int q=0;
			    for(q=N.rpos[brow];q<t;q++){
				    int ccol=N.data[q].j;
				    ctemp[ccol]=M.data[p].v*N.data[q].v;
			    }
		    }
		    int ccol=0;
		    for(ccol=1;ccol<=Q->nu;ccol++){
			    if(ctemp[ccol]){
			  	if(++Q->tu>MAXSIZE) return ERROR;
			  	Q->data[Q->tu].i=arow;
			  	Q->data[Q->tu].j=ccol;
			  	Q->data[Q->tu].v=ctemp[ccol];
			    }
		    } 
	    }
    }
} 

//¥Ú”°æÿ’Û
void PrintfMatrix(RLSMatrix M){
	int i=0;
	for(i=1;i<=M.tu;i++){
		printf("(%d,%d,%d)\n",M.data[i].i,M.data[i].j,M.data[i].v);
	}
} 
int main(){
	RLSMatrix M,N,Q;
	//≥ı ºªØæÿ’ÛM
	InitMatrix(&M,3,4,4);
	M.data[1] = (Triple){1, 3, 3};
    M.data[2] = (Triple){2, 1, 4};
    M.data[3] = (Triple){3, 2, 5};
    M.data[4] = (Triple){3, 3, 6};
    M.rpos[1] = 1;
    M.rpos[2] = 2;
    M.rpos[3] = 3;
    //≥ı ºªØæÿ’ÛN°£
	InitMatrix(&N,4,2,4);
	N.data[1] = (Triple){1, 1, 7};
    N.data[2] = (Triple){2, 2, 10};
    N.data[3] = (Triple){3, 1, 11};
    N.data[4] = (Triple){4, 2, 12};
    N.rpos[1] = 1;
    N.rpos[2] = 2;
    N.rpos[3] = 3;
    N.rpos[4] = 4;
    //æÿ’Ûœ‡≥À
	if(MultSMatrix(M,N,&Q)){
		printf("Rwsultant matrixQ:\n");
		PrintfMatrix(Q);
	} else{
		printf("Matrix multiplication failed.\n");
	}
	return 0;
}




