#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "course.h"


int N1;
struct course *c_head;

int main()
{
	c_menu();
}

/*保存课程信息*/
void c_save(struct course *c_head)
{
	FILE * fp;
	struct course * p;
	if((fp=fopen(COU_F,"w"))==NULL) //对文件内容进行覆盖
	{
		printf("\n保存失败!"); 
		exit(0); 
	}
	p = c_head;
	while(p!=NULL){
		fprintf(fp,"%d %s %s %d %d %d %d\n",p->c_num,p->c_name,p->type,p->time,p->stu_num,p->score,p->limit);
		p=p->next;      //p_head指向下一个节点
	}
	fclose(fp); //保存文件，清空缓冲区
	printf("课程信息已保存!\n"); 
}

/*根据课程号查找课程*/
struct course *find_num(struct course *c_head,int num){
	struct course *p,*q;
	p=c_head;
	q=NULL;
	while (p != NULL){
		if (num == p->c_num)
			return q;
		q = p;
		p = p->next;
	}
	return q;
}

/*课程管理主页面*/
void c_menu()
{

int num;
while(num<=5){
	printf(" \n                    \n");
	printf("*********************课程管理功能菜单*************************       \n");
	printf("     *********************************************     \n");
	printf("     * 1.从文件中录入课程信息  * *  2.添加课程信息   *     \n");
	printf("     *********************************************     \n");
	printf("     * 3.删除课程信息          * *  4.查询课程信息        *     \n");
	printf("     *********************************************     \n");
	printf("     * 5.修改课程信息          * *  6.返回主菜单             \n");
	printf("     *********************************************  \n");
	printf("     ----------------------   ----------------------   \n");
	printf("请选择编号:");
	scanf("%d", &num);
	switch (num)
	{
		case 1:
			load_cou();
			break;
		case 2:
			c_insert(c_head); 
			break;
		case 3:
			c_delete(c_head);
			break;
		
		case 4:
			c_show(c_head);
			break;
		case 5:
			c_modify(c_head);
			break;
		case 6:
			break;
	}
}
}

/*录入课程信息子函数*/
void load_cou()
{
	FILE * fp;
	struct course *p1,*p2;
	N1 = 0;
	int i;
	if((fp=fopen(COU_F,"r"))==NULL) { 
		printf("找不到文件!\n"); 
		exit(0); 
	} 
	p1=p2=(struct course*)malloc(sizeof(struct course));
	fscanf(fp,"%d%s%s%d%d%d%d",&p1->c_num,&p1->c_name,&p1->type,&p1->time,&p1->stu_num,&p1->score,&p1->limit);
	c_head = NULL;
	while(!feof(fp)){
		N1 = N1 + 1;
		if(N1 == 1)
			c_head = p1;
		else
			p2->next = p1;
		p2 = p1;
		p1=(struct course * )malloc(sizeof(struct course));
		fscanf(fp,"%d%s%s%d%d%d%d",&p1->c_num,&p1->c_name,&p1->type,&p1->time,&p1->stu_num,&p1->score,&p1->limit);
	}
	p2->next=NULL;
	printf("录入课程信息成功！\n");
}


/*添加课程函数*/
void c_insert(struct course *c_head){
	struct course *p,*p0,*p1,*p2;
	int i;
	p=(struct course *)malloc(sizeof(struct course));
	printf("请输入课程号:");
	scanf("%d",&p->c_num);
	printf("请输入课程名称:");
	scanf("%s",&p->c_name);
	printf("请输入课程性质:");
	scanf("%s",&p->type);
	printf("请输入授课学时:");
	scanf("%d",&p->time);
	printf("请输入课程已选人数:");
	scanf("%d",&p->stu_num);
	printf("请输入课程学分:");
	scanf("%d",&p->score);
	printf("请输入课程人数上限:");
	scanf("%d",&p->limit);
	p1=c_head;
	p0=p;
	if(c_head == NULL){
		c_head = p0;
		p0->next=NULL;
	}
	else{
		while((p0->c_num > p1->c_num) && (p1->next!=NULL)){
			p2=p1;
			p1=p1->next;
		}
		if(p0->c_num <= p1->c_num){
			if(c_head==p1)
				c_head=p0;
			else
				p2->next=p0;
			p0->next=p1;
		}
		else{
			p1->next=p0;
			p0->next=NULL;
		}
	}
	N1=N1+1;
	c_save(c_head);
}

/*删除课程信息*/
void c_delete(struct course *c_head){
	int num;
	printf("请输入要删除的课程号：\n");
	scanf("%d",&num);
	struct course *p1,*p2;
	if(c_head == NULL){
		printf("\n没有课程,无法删除!\n");
		goto end;
	}
	p1=c_head;
	while(num != p1->c_num && p1->next!=NULL){
		p2=p1;
		p1=p1->next;
 	}
 	if(num == p1->c_num){
		if(p1 == c_head)
			c_head = p1->next;
		else
			p2->next = p1->next;
		printf("已删除该课程!\n");
		N1 = N1-1;
		c_save(c_head);
	}
	else
		printf("无该课程号课程!\n");
	end:;
}

/*查询课程详情*/
void c_show(struct course *c_head)
{
	struct course *p;
	p=c_head;
	while (p != NULL)
	{
		printf("\n\t\t------------------------------------------------------");
 		printf("\n\t\t课程号：%d", p->c_num);
		printf("\t\t课程名称：%s", p->c_name);
		printf("\n\t\t课程性质：%s", p->type);
		printf("\t\t授课学时：%d", p->time);
		printf("\n\t\t课程学分：%d", p->score);
		printf("\t\t课程人数上限：%d", p->limit);
		printf("\n\t\t课程已选人数：%d", p->stu_num);
		printf("\n\t\t------------------------------------------------------");
		p=p->next;
	}
}

struct course *load_end(struct course *c_head)
{
	struct course *p;
	while (c_head != NULL){
		p = c_head;
		c_head = c_head->next;
	}
	return p;
}

/*根据课程号修改课程信息*/
void c_modify(struct course *c_head){
	struct course *find=NULL;
	struct course *c_tail=load_end(c_head);
	int num;
	printf("请输入要修改的课程编号：\n");
	scanf("%d",&num);
	find = find_num(c_head,num);
	if (find == c_tail){
		printf("\n\t\t你所查找的课程不存在！\n");
	}
	else{
		if (find == NULL)
			find = c_head;
		else
			find = find->next;
		printf("\n\t\t原课程名称:%s  修改后的课程名称：", find->c_name);
		scanf("%s", &find->c_name);
		printf("\n\t\t原课程性质:%s  修改后的课程性质：", find->type);
		scanf("%s", &find->type);
		printf("\n\t\t原授课学时:%d  修改后的授课学时：", find->time);
		scanf("%d", &find->time);
		printf("\n\t\t原课程学分:%d  修改后的课程学分：", find->score);
		scanf("%d", &find->score);
		printf("\n\t\t原课程人数:%d  修改后的课程人数：", find->stu_num);
		scanf("%d", &find->stu_num);
		printf("\n\t\t原课程人数上限:%d  修改后的课程人数上限：", find->limit);
		scanf("%d", &find->limit);
		printf("\t\t修改完成！\n\n");
		c_save(c_head);
	}
}
