
#ifndef COUNT_H
#define COUNT_H
#include "count.h"
#endif


/*void count1(int a){
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
}*/
int money=0;
void keep_account(int a){
	
	switch(a){
		case 1:
			money+=20;
			break;
		case 2:
			money+=10;
			break;
		case 3:
		    money+=15;
		    break;
		case 4:
		    money+=15;
		    break;
		case 5:
		    money+=20;
		    break;

    }

}

int Return_change(int a){
	return (a-money);
}