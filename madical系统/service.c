#include <stdio.h>
#include <stdlib.h>


#ifndef SERVICE_H
#define SERVICE_H
#include "service.h"
#endif


/*#ifndef DIDPALY_C
#define DIDPALY_C
#include "dispaly.c"
#endif*/


/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int (*dispaly[7])();
int main(int argc, char *argv[]) {
	int a=0;
	int b=0;
	dispaly[0]=dispaly1;
	dispaly[1]=dispaly2;
	dispaly[2]=dispaly7;
	dispaly[3]=dispaly4;
	dispaly[4]=dispaly5;
	dispaly[5]=dispaly6;
	dispaly[6]=dispaly7;
	int choice=0;
	do{
		choice=dispaly0();
	    
	    if(choice==1){
	    	choice=dispaly[choice-1]();
	    	b=chef(choice);
	    	keep_account(choice);
		}
		if(choice==2){
			choice=dispaly[choice-1]();
	    	b=chef(choice+3);
	    	keep_account(choice+3);
		}
	    if(b==1){
	    	printf("你是否购买结束：0.是  1.否\n");
	    	scanf("%d",&a);
		}else printf("药物以售罄");
	    
	    system("cls");
	}while(a);
	while(1){
		choice=dispaly[3]();
	    dispaly[choice+3]();
	}
	
	
	return 0;
}