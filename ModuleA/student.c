#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "student.h"


int N;
struct student *head;

int main()
{
	head=load_stu();
	menu();

}

/*录入学生信息子函数*/
struct student *load_stu()
{
	int i=0;
	FILE * fp;
	struct student *p1,*p2;
	N=0;
	if((fp=fopen(STU_F,"r"))==NULL) 
	{
		printf("找不到文件!\n"); 
		exit(0); 
	}
	struct student* temp = (struct student*)malloc(sizeof(struct student));
	while (!feof(fp)){
		if (fread(temp, sizeof(struct student), 1, fp))
			N++;
	}
	free(temp);
	temp = NULL;
  
	if (N == 0)
		return NULL;
	else{
		rewind(fp);
		struct student *p_head = NULL;//文件中有链表信息，则创建一个头指针
		p_head = (struct student*)malloc(sizeof(struct student));
		fread(p_head, sizeof(struct student), 1, fp);//用文件内容初始化链表节点
		p_head->next = NULL;
		struct student* p_new = p_head;
		struct student* p_end = p_head;
		for (i = 0; i < N; i++){
			p_new = (struct student*)malloc(sizeof(struct student));
			fread(p_new, sizeof(struct student), 1, fp);
			printf("%d\n",p_end->num);
			p_new->next = NULL;
			p_end->next = p_new;
			p_end = p_new;
		}
		fclose(fp);
		return p_head;
	}
}

/*保存学生信息*/
void s_save(struct student *head)
{
	FILE * fp;
	struct student * p;
	if((fp=fopen(STU_F,"w"))==NULL) //对文件内容进行覆盖
	{
		printf("\n保存失败!"); 
		exit(0); 
	}
	p=head;
	while(p!=NULL){
		fprintf(fp,"%d %s %d %d ",p->num,p->name,p->course_sum,p->score_sel);
		int j;
		for(j=0;j<(p->course_sum);j++)
			fprintf(fp,"%s",p->course[j]);
		fprintf(fp,"\n");
		p=p->next;      //p_head指向下一个节点
	}
	fclose(fp); //保存文件，清空缓冲区
	printf("学生信息已保存!\n"); 
}

/*学生管理主页面*/
void menu()
{
	int num;
	while(num!=7){
	printf(" \n                    \n");
	printf("  ******************************************************\n\n");
	printf("  *                学生信息管理系统                    *\n \n");
	printf("  ******************************************************\n\n");
	printf("*********************系统功能菜单*************************       \n");
	printf("     *********************************************     \n");
	printf("     * 1.添加学生信息          * *  2.按学号查询学生信息   *     \n");
	printf("     *********************************************     \n");
	printf("     * 3.按姓名查询学生信息     * *  4.删除学生信息        *     \n");
	printf("     *********************************************     \n");
	printf("     * 5.按姓名修改学生信息    * *  6.按学号修改学生信息   *     \n");
	printf("     *********************************************     \n");
	printf("     * 7.退出系统             \n");
	printf("     **********************  \n");
	printf("     ----------------------   ----------------------   \n");
	printf("请选择菜单编号:");
	scanf("%d", &num);
	switch (num)
	{
		case 1:
			s_insert(head); 
			break;
		case 2:
			s_show_num(head);
			break;
		/*
		case 3:
			s_show_name(head);
			break;
		case 4:
			s_delete(head);
			break;
		case 5:
			s_modify_name(head);
			break;
		case 6:
			s_modify_num(head);
			break;
		case 7:
			printf("即将退出程序!\n");
			break;*/
		default:printf("请在1-7之间选择\n");
	}
}
}


void s_show_num(struct student *head)
{
	
	struct student *p;
	p = head;
	while (p != NULL)
	{
		printf("\n\t\t------------------------------------------------------");
 		printf("\n\t\t学号：%d", p->num);
		printf("\n\t\t姓名：%s", p->name);
		printf("\n\t\t已选课程:\n");
		int i;
		for (i = 0; i < p->course_sum; i++)
			printf("\t\t\t[%d]:%s\n", i + 1, p->course[i]);
		printf("\t\t选课总数：%d", p->course_sum);
		printf("\n\t\t已选课程总学分：%d", p->score_sel);
		printf("\n\t\t------------------------------------------------------");
		p = p->next;
	}
}

/*添加学生函数*/
void s_insert(struct student *head){
	struct student *p,*p0,*p1,*p2;
	int i;
	p=(struct student *)malloc(sizeof(struct student));
	printf("请输入学生学号:");
	scanf("%d",&p->num);
	printf("请输入学生姓名:");
	scanf("%s",&p->name);
	printf("请输入学生选课总数:");
	scanf("%d",&p->course_sum);
	printf("请输入学生已选课总学分:");
	scanf("%d",&p->score_sel);
	for(i=0;i<(p->course_sum);i++){
		printf("请输入学生所选课程名称:");
		scanf("%s",&p->course[i]);
	}
	p1=head;
	p0=p;
	if(head==NULL){
		p->next = NULL;
		head = p;
	}
	else{
		while((p0->num > p1->num) && (p1->next!=NULL)){
			p2=p1;
			p1=p1->next;
		}
		if(p0->num <= p1->num){
			if(head==p1)
				head=p0;
			else
				p2->next=p0;
			p0->next=p1;
		}
		else{
			p1->next=p0;
			p0->next=NULL;
		}
	}
	N=N+1;
	s_save(head);
}
