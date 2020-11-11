#include<stdio.h>
#include"student.h"




/* 学生管理主页面*/
void menu()
{
	int num;
	printf(" \n\n                    \n\n");
	printf("  ******************************************************\n\n");
	printf("  *                学生信息管理系统                    *\n \n");
	printf("  ******************************************************\n\n");
	printf("*********************系统功能菜单*************************       \n");
	printf("     *********************************************     \n");
	printf("     * 1.查询学生信息    * *  2.修改学生信息   *     \n");
	printf("     *********************************************     \n");
	printf("     * 3.添加学生信息    * *  4.按学号删除信息 *     \n");
	printf("     *********************************************     \n");
	printf("     * 5.显示当前信息    * *  6.保存当前学生信息*     \n");
	printf("     ********************** **********************     \n");
	printf("     * 7.退出系统        *                            \n");
	printf("     **********************                            \n");
	printf("     ----------------------   ----------------------                           \n");
	printf("请选择菜单编号:");
	scanf("%d", &num);
	switch (num)
	{
	case 1:seek(); break;
	case 2:modify(); break;
	case 3:insert(); break;
	case 4:del(); break;
	case 5:display(); break;
	case 6:save(); break;
	case 7:
		k = 0; 
		printf("即将退出程序!\n");
		break;
	default:printf("请在0-8之间选择\n");
	}
}

/*添加学生信息*/
void insert()
{
	int i = n, j, flag;
	printf("请输入待增加的学生数:\n");
	scanf("%d", &m);
	if (m > 0){
		do
		{
			flag = 1;
			while (flag)
			{
				flag = 0;
				printf("请输入第%d位学生的学号:\n", i + 1);
				scanf("%s", stu[i].StudentId);
				for (j = 0; j < i; j++){
					if (strcmp(stu[i].StudentId, stu[j].StudentId) == 0){
						printf("该学号已存在，请重新输入！\n");
						flag = 1;
						break;
					}
				}
			}
			printf("请输入第%d 个学生的姓名:\n", i+1);
			scanf("%s", stu[i].StudentName);
			printf("请输入第%d 个学生的年龄:\n", i+1);
			scanf("%d", &stu[i].StudentAge);
			printf("请输入第%d 个学生的性别:\n", i+1);
			scanf(" %c", &stu[i].StudentSex);
			printf("请输入第%d 个学生的C语言成绩\n",i+1);
			scanf("%f", &stu[i].score[0]);
			printf("请输入第%d 个学生的高等数学成绩:\n", i+1);
			scanf("%f", &stu[i].score[1]);
			printf("请输入第%d 个学生的大学英语成绩:\n", i+1);
			scanf("%f", &stu[i].score[2]);
			if (0 == flag){
				i++;
			}
		} while (i<n + m);
	}
		n += m;
		printf("学生信息增加完毕！！！\n");
		system("pause");
}

/*根据学号或者姓名查看学生信息*/
void seek()
{
	int i, item, flag;
	char s1[21]; /* 以姓名和学号最长长度+1为准*/
	printf("------------------\n");
	printf("-----1.按学号查询-----\n");
	printf("-----2.按姓名查询-----\n");
	printf("-----3.退出本菜单-----\n");
	printf("------------------\n");
	while (1)
	{
		printf("请选择子菜单编号:");
		scanf("%d", &item);
		flag = 0;
		switch (item)
		{
		case 1:
			printf("请输入要查询的学生的学号:\n");
			scanf("%s", s1);
			for (i = 0; i<n; i++)
			if (strcmp(s1,stu[i].StudentId) == 0)
			{
				flag = 1;
				printf("学生学号\t学生姓名\t年龄\t性别\tC语言成绩\t高等数学\t大学英语成绩\n");
				printf("--------------------------------------------------------------------\n");
				printf("%s\t%s\t%d\t%6\t%.1f\t%.1f\t%.1f\n", stu[i].StudentId,stu[i].StudentName,stu[i].StudentAge,stu[i].StudentSex,stu[i].score[0],stu[i].score[1],stu[i].score[2]);
			}
			if (0 == flag)
				printf("该学号不存在！\n"); break;
		case 2:
			printf("请输入要查询的学生的姓名:\n");
			scanf("%s", s1);
			for (i = 0; i<n; i++)
			if (strcmp(stu[i].StudentName, s1) == 0)
			{
				flag = 1;
				printf("学生学号\t学生姓名\t年龄\t性别\tC语言成绩\t高等数学\t大学英语成绩\n");
				printf("--------------------------------------------------------------------\n");
				printf("%s\t%s\t%d\t%c\t%.1f\t%.1f\t%.1f\n", stu[i].StudentId, stu[i].StudentName, stu[i].StudentAge, stu[i].StudentSex, stu[i].score[0], stu[i].score[1], stu[i].score[2]);
			}
			if (0 == flag)
				printf("该姓名不存在！\n"); break;
		case 3:return;
		default:printf("请在1-3之间选择\n");
		}
	}
}



