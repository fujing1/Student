#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	FILE * fp;
	struct student *p1,*p2;
	N = 0;
	int i;
	if((fp=fopen(STU_F,"r"))==NULL) { 
		printf("找不到文件!\n"); 
		exit(0); 
	} 
	p1=p2=(struct student*)malloc(sizeof(struct student));
	fscanf(fp,"%d%s%d%d",&p1->num,&p1->name,&p1->course_sum,&p1->score_sel,&p1->course);
		for(i=0;i<(p1->course_sum);i++)
			fscanf(fp,"%s",&p1->course[i]);
	head = NULL;
	while(!feof(fp)){
		N = N + 1;
		if(N == 1)
			head = p1;
		else
			p2->next = p1;
		p2=p1;
		p1=(struct student * )malloc(sizeof(struct student));
		fscanf(fp,"%d%s%d%d",&p1->num,&p1->name,&p1->course_sum,&p1->score_sel);
		for(i=0;i<(p1->course_sum);i++)
			fscanf(fp,"%s",&p1->course[i]);
	} 
	p2->next=NULL;
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
			fprintf(fp,"%s ",p->course[j]);
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
	printf(" \n                    \n");
	printf("*********************学生管理功能菜单*************************       \n");
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
		
		//case 3:
		//	s_show_name(head);
		//	break;
		case 4:
			s_delete(head);
			break;
/*
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
	if(head == NULL){
		head = p0;
		p0->next=NULL;
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
	end:;
}

/*按照学号查询*/
void s_show_num(struct student *head)
{
	
	struct student *p;
	p = head;
	int num1,flag=0;
	printf("请输入要查询的学生的学号：\n");
	scanf("%d",&num1);
	while (p != NULL)
	{
		if ( num1 == p->num){
			flag=1;
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
	if(flag == 0)
		printf("无该学号学生!\n");
}

/*删除学生信息*/
void s_delete(struct student *head){
	int num1;
	printf("请输入要删除的学生的学号：\n");
	scanf("%d",&num1);
	struct student *p1,*p2;
	if(head==NULL){
		printf("\n没有学生,无法删除!\n");
		goto end;
	}
	p1=head;
	while(num1!=p1->num && p1->next!=NULL){
		p2=p1;
		p1=p1->next;
 	}
 	if(num1==p1->num){
		if(p1==head)
			head = p1->next;
		else
			p2->next = p1->next;
		printf("已删除该学号学生!\n");
		N=N-1;
		s_save(head);
	}
	else
		printf("无该学号学生!\n");
	end:;
}
