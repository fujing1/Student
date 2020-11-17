#include<stdio.h>
#include"student.h"
#include"course.h"
int main(void)
{
	int num;
	start:
  	printf(" \n                    \n");
	printf("*********************学生选课管理系统*************************       \n");
	printf("     *********************************************     \n");
	printf("     * 1.学生信息管理       \n");
	printf("     *********************************************     \n");
	printf("     * 2.课程信息管理        \n");
	printf("     *********************************************     \n");
	printf("     * 3.退出系统          \n");
	printf("     *********************************************     \n");
	printf("     ----------------------------------------------------   \n");
	printf("请选择菜单编号:");
	scanf("%d", &num);
	switch(num){
		case 1:{
			system("cls");
			s_menu();
			goto start;
			break;
		}
		case 2:{
			system("cls");
			c_menu();
			goto start;
			break;
		}
		case 3:{
			printf("即将退出本系统！\n");
			break;
		}
}
