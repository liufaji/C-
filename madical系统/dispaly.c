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
int dispaly0(){
	
	printf("\n==========选择你需要购买的药类===========\n");
	printf("1.发烧类药物\n");
	printf("2.感冒类药物\n");
	printf("3.Exit\n");
	scanf("%d",&choice);
	system("cls");
	return choice;
}
	
int dispaly1(){
	printf("\n==========选择你要购买的发烧类药物===========\n");
	printf("1.   对乙酰氨基酚   20元\n");
	printf("2.   布洛芬         10元\n");
	printf("3.    阿司匹林     15元\n");
	scanf("%d",&choice);
	system("cls");
	return choice;
	
}
int dispaly2(){
	printf("\n============选择你要购买的感冒类药物==============\n");
	printf("1.板蓝根颗粒       15元\n");
    printf("2. 999感冒灵       20元\n");
    scanf("%d",&choice);
	system("cls");
	return choice;

	
	
	
}
void dispaly5(){
	printf("===================================================\n");
	extern int money;
	printf("you bill is %d\n",money);
	system("pause"); 
	system("cls");
	
}
void dispaly6(){
	printf("\n================================================\n");
	printf("please input your money\n");
	int a=0;
	scanf("%d",&a);
	int b=Return_change(a);
	printf("change you back %d\n",b);
	system("pause"); 
	system("cls");
	extern int money;
	money=0;
	
}
void dispaly7(){
	exit(0);
}
int dispaly4(){
	printf("\n=================================================\n");
	printf("1.查看你的账单\n");
	printf("2.支付你的账单\n");
	printf("3.Exit\n");
	scanf("%d",&choice);
	system("cls");
	return choice;
}
	