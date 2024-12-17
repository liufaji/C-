#ifndef DIDPALY_H
#define DIDPALY_H
#include "dispaly.h"
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif


int choice=0;
void dispaly1(){
	printf("\n=====================\n");
	printf("1.show the menu\n");
	printf("2.show the bill\n");
	printf("3.pay the menu\n");
	printf("4.Exit\n");
	scanf("%d",&choice);
	system("cls");
	count1(choice);
}

void dispaly2(){
	printf("\n==============今日供应============\n");
	printf("1.西红柿炒鸡蛋    12.5\n");
	printf("2.辣椒炒土豆丝    6.5\n");
	printf("3.凉拌黄          3.5\n");
	printf("\n=====================================\n");
	scanf("%d",&choice);
	system("cls");
	int a=chef(choice);
	if(a=0){
		dispaly6();
	}else{
		keep_account(choice);
	}
	
	
	
}
void dispaly3(){
	printf("======================================\n");
	extern double money;
	printf("you bill is %lf\n",money);
	system("pause"); 
	system("cls");
	dispaly1();
}
void dispaly4(){
	printf("\n===========================\n");
	printf("please input your money\n");
	double a=0;
	scanf("%lf",&a);
	double b=Return_change(a);
	printf("change you back %lf\n",b);
	system("pause"); 
	system("cls");
	extern double money;
	money=0;
	dispaly1();
}
void dispaly5(){
	exit(0);
}
void dispaly6(){
	printf("\n=========订餐失败=========\n");
	system("pause"); 
	system("cls");
	dispaly2();
}
	