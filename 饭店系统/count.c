
#ifndef COUNT_H
#define COUNT_H
#include "count.h"
#endif


void count1(int a){
	switch(a){
		case 1:
			dispaly2();
			break;
		case 2:
			dispaly3();
			break;
		case 3:
		    dispaly4();
		    break;
		case 4:
		    dispaly5();
			break;	
	}
}
double money=0;
void keep_account(int a){
	
	switch(a){
		case 1:
			money+=12.5;
			break;
		case 2:
			money+=6.5;
			break;
		case 3:
		    money+=3.5;
		    break;

    }
    dispaly1();
}

double Return_change(double a){
	return (a-money);
}