#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef struct{
	int* elem;
	int listsize;
	int length;
}SpList;
void MergeList_Sp(SpList* La,SpList* Lb,SpList* Lc){
	int* pa=La->elem;
	int* pb=Lb->elem;
	Lc->listsize=Lb->length+La->length;
	int* pc=Lc->elem=(int*)malloc(Lc->listsize*sizeof(int));
	if(!Lc->elem){
		exit(-2);
	}
	int* pa_last=La->elem+La->length-1;
	int* pb_last=Lb->elem+Lb->length-1;
	while(pa<=pa_last&&pb<=pb_last){
		if(*pa<=*pb){
			*pc++=*pa++;
		}else *pc++=*pb;
	}
	while(pa<=pa_last){
		*pc++=*pa++;
	}
	while(pb<=pb_last){
		*pc++=*pb++;
	}
}


int main(){
	SpList La;
	SpList Lb;
	SpList Lc;
	MergeList_Sp(&La,&Lb,&Lc);
}