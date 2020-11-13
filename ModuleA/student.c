#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "student.h"



struct student *stu_head;
struct student *stu_tail;

int main()
{
	/*对指针变量初始化*/
	stu_head = load_stu();    //stu_head指向学生链表头
	stu_tail = locate_end(stu_head);  //stu_tail指向学生链表尾
	menu();

}

/*stu_head指向学生链表头*/
struct student* load_stu()
{
	int count = 0;
	FILE *fp;
	if ((fp = fopen(STU_F, "r")) == NULL){
		printf("\t\tcannot open the file:STU_F\n");
		exit(0);
	}
	struct student* temp = (struct student* )malloc(sizeof(struct student));
	while (!feof(fp)){
		if (fread(temp, sizeof(struct student), 1, fp))
 			count++;
	}
	free(temp);
	temp = NULL;
  
	if (count == 0)
		return NULL;
	else{
		rewind(fp);
		struct student *p_head = NULL;//文件中有链表信息，则创建一个头指针
		p_head = (struct student* )malloc(sizeof(struct student));
		fread(p_head, sizeof(struct student), 1, fp);//用文件内容初始化链表节点
		p_head->next = NULL;
		count--;
		struct student* p_new = p_head;
		struct student* p_end = p_head;
		int i;
		for (i = 0; i < count; i++){
			p_new = (struct student* )malloc(sizeof(struct student));
			fread(p_new, sizeof(struct student), 1, fp);
			p_new->next = NULL;
			p_end->next = p_new;
			p_end = p_new;
		}
		fclose(fp);
		return p_head;
	}
}

/*stu_tail指向学生链表尾*/
struct student * locate_end(struct student * head){
	struct student* end = head;
	while (head != NULL){
		end = head;
		head = head->next;
	}
	return end;
}

//存储学生信息
void store_stu(struct student * p_head)
{
	FILE *fp;
	if ((fp = fopen(STU_F, "w")) == NULL)//以只写方式打开文件，覆盖以前数据
	{
		printf("\t***STU_F missed,please quit the system and check for that!\n\n");
		exit(0);
	}
	while (p_head != NULL)//将链表所有节点写入缓冲区
	{
		fwrite(p_head, sizeof(struct student), 1, fp);//将链表一个节点写入缓冲区
		p_head = p_head->next;      //p_head指向下一个节点
	}
	fclose(fp);//保存文件，清空缓冲区
}

/*按照学号查找学生*/
struct student* studentnamefind_num(struct student *head, char tar[])
{
	struct student *p, *q;
	p = head;
	q = NULL;
	while (p != NULL){
		if (strcmp(tar, p->num) == 0)
			return q;
		q = p;
		p = p->next;
	}
	return q;
}

//计算学生数量
int link_count(struct student * head)
{
	int count = 0;
	while (head != NULL){
		count++;
		head = head->next;
	}
	return count;
}

/*判断输入值是否为数字*/
int judge_ascii_num(char in[])
{
	int i = 0;
	while (in[i]!='\0'){
		if ((in[i] < '0') || (in[i] > '9'))
			return 0;
		i++;
	}
	return 1;
}

//学生管理主页面
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
	printf("     * 5.显示当前信息    * *  6.查看所有学生信息*     \n");
	printf("     ********************** **********************     \n");
	printf("     * 7.退出系统        *                            \n");
	printf("     **********************                            \n");
	printf("     ----------------------   ----------------------                           \n");
	printf("请选择菜单编号:");
	scanf("%d", &num);
	switch (num)
	{
	/*case 1:seek(); break;
	case 2:modify(); break;
	case 3:s_insert(); break;
	case 4:del(); break;
	case 5:display(); break;*/
	case 6:
		s_show(stu_head);
		break;
	case 7:
		printf("即将退出程序!\n");
		break;
	default:printf("请在1-7之间选择\n");
	}
}

/*展示所有学生信息*/
void s_show(struct student *head)
{
	
	struct student *p;
	p = head;
	printf("\n\t\t学号：%s", p->num);
	while (p != NULL)
	{
		printf("\n\t\t------------------------------------------------------");
 		printf("\n\t\t学号：%s", p->num);
		printf("\n\t\t姓名：%s", p->name);
		printf("\n\t\t已选课程:\n");
		int i;
		for (i = 0; i < p->course_sum; i++)
			printf("\t\t\t[%d]:%s\n", i + 1, p->course[i]);
		printf("\t\t选课总数：%d", p->course_sum);
		printf("\n\t\t已选课程总学分：%lf", p->score_sel);
		printf("\n\t\t------------------------------------------------------");
		p = p->next;
	}
}

/*添加学生函数*/
void s_insert(struct student *head){
	while (1){
		char input[50];
		while (1){
			printf("\n\t\t请输入要添加学生的学号(数字)，返回上级菜单请输入0000：");
			scanf("%s", input);
			while (getchar() != '\n');
				if (judge_ascii_num(input) == 1)
					break;
				else
					printf("\n\t\t####输入错误！#####");
		}
		if (strcmp(input, "0000") == 0)
			break;
		if (studentnamefind_num(stu_head, input) != stu_tail){
			printf("\t\t###已存在该学生,请重新输入!####\n");
			continue;
		}
  
		/*初始化学生信息*/
		struct student* p = (struct student *)malloc(sizeof(struct student));
		strcpy(p->num, input);
		printf("\t\t请输入学生姓名:");
		scanf("%s", p->name);
		printf("\t\t请输入选课数：");
		scanf("%d", p->course_sum);
		printf("\t\t请输入已选课总学分");
		while (getchar() != '\n');
			printf("\t\t请输入当前该学生总学分:");
		p->score_all = input_double();
		p->course_sum = 0;
		p->score_sel = 0.0;
		strcpy(p->password, p->num);
		//当前链表中没有节点
		if (stu_head == NULL){
			p->next = NULL;
			stu_head = p;
			stu_tail = p;
		}
		else{
			//新增节点的标号比头节点还小
			if (strcmp(p->num, stu_head->num) < 0){
				p->next = stu_head;
				stu_head = p;
			}
			//新增节点的标号比尾节点还大
			else if (strcmp(p->num, stu_tail->num) > 0){
				p->next = NULL;
				stu_tail->next = p;
				stu_tail = p;
			}
			else{
				struct student* temp = stu_head;
				while (temp != stu_tail){
					if (strcmp(p->num, temp->num) > 0){
						p->next = temp->next;
						temp->next = p;
						break;
					}
				}
			}
		}
		printf("\n\t\t学生信息录入成功!\n");
	}
	store_stu(stu_head);
}


