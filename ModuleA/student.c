#include "def.h"

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
	printf("学生信息更新成功!\n"); 
}

struct student *load_end(struct student *head)
{
	struct student *p;
	while (head != NULL){
		p = head;
		head = head->next;
	}
	return p;
}

/*根据学号查找学生*/
struct student *find_num(struct student *head,int num){
	struct student *p,*q;
	p=head;
	q=NULL;
	while (p != NULL){
		if (num == p->num)
			return q;
		q = p;
		p = p->next;
	}
	return q;
}

/*根据姓名查找学生*/
struct student *find_name(struct student *head,char name[]){
	struct student *p,*q;
	p=head;
	q=NULL;
	while (p != NULL){
		if (strcmp(name,p->name)==0)
			return q;
		q = p;
		p = p->next;
	}
	return q;
}

/*录入学生信息子函数*/
void load_stu()
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
	printf("录入学生信息成功！\n");
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
}

/*按照学号查询*/
void s_show_num(struct student *head)
{
	
	struct student *p=NULL;
	struct student *tail=load_end(head);
	int num;
	printf("请输入要查找的学号：\n");
	scanf("%d",&num);
	p = find_num(head,num);
	if (p == tail){
		printf("\n\t\t你所查找的学生不存在！\n");
	}
	else{
		if (p == NULL)
			p = head;
		else
			p = p->next;
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

/*按照姓名查询*/
void s_show_name(struct student *head)
{
	
	struct student *p=NULL;
	struct student *tail=load_end(head);
	char name[MAXN];
	printf("请输入要查找的学生姓名：\n");
	scanf("%s",&name);
	p = find_name(head,name);
	if (p == tail){
		printf("\n\t\t你所查找的学生不存在！\n");
	}
	else{
		if (p == NULL)
			p = head;
		else
			p = p->next;
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

/*根据学号修改学生信息*/
void s_modify_num(struct student *head){
	struct student *p=NULL;
	struct student *tail=load_end(head);
	int num;
	printf("请输入要查找的学号：\n");
	scanf("%d",&num);
	p = find_num(head,num);
	if (p == tail){
		printf("\n\t\t你所查找的学生不存在！\n");
	}
	else{
		if (p == NULL)
			p = head;
		else
			p = p->next;
		printf("\n\t\t原学生学号:%d  修改后的学生姓名：", p->num);
		scanf("%d", &p->num);
		printf("\n\t\t原学生姓名:%s  修改后的学生姓名：", p->name);
		scanf("%s", &p->name);
		int sum;
		sum = p->course_sum;
		printf("\n\t\t原选课总数:%d  修改后的选课总数：", p->course_sum);
		scanf("%d", &p->course_sum);
		printf("\n\t\t原课程学分:%d  修改后的课程学分：", p->score_sel);
		scanf("%d", &p->score_sel);
		printf("\n\t\t原选课程:\n");
		int i;
		for (i = 0; i < sum; i++)
			printf("\t\t\t[%d]:%s\n", i + 1, p->course[i]);
		printf("\n\t\t修改后所选课程:\n");
		for (i = 0; i < p->course_sum; i++){
			printf("\t\t\t[%d]:",i + 1);
			scanf("%s", &p->course[i]);
		}
		printf("\t\t修改完成！\n\n");
		s_save(head);
	}
}

/*根据姓名修改学生信息*/
void s_modify_name(struct student *head){
	struct student *p=NULL;
	struct student *tail=load_end(head);
	char name[MAXN];
	printf("请输入要查找的学生姓名：\n");
	scanf("%s",&name);
	p = find_name(head,name);
	if (p == tail){
		printf("\n\t\t你所查找的学生不存在！\n");
	}
	else{
		if (p == NULL)
			p = head;
		else
			p = p->next;
		printf("\n\t\t原学生学号:%d  修改后的学生姓名：", p->num);
		scanf("%d", &p->num);
		printf("\n\t\t原学生姓名:%s  修改后的学生姓名：", p->name);
		scanf("%s", &p->name);
		int sum;
		sum = p->course_sum;
		printf("\n\t\t原选课总数:%d  修改后的选课总数：", p->course_sum);
		scanf("%d", &p->course_sum);
		printf("\n\t\t原课程学分:%d  修改后的课程学分：", p->score_sel);
		scanf("%d", &p->score_sel);
		printf("\n\t\t原选课程:\n");
		int i;
		for (i = 0; i < sum; i++)
			printf("\t\t\t[%d]:%s\n", i + 1, p->course[i]);
		printf("\n\t\t修改后所选课程:\n");
		for (i = 0; i < p->course_sum; i++){
			printf("\t\t\t[%d]:",i + 1);
			scanf("%s", &p->course[i]);
		}
		printf("\t\t修改完成！\n\n");
		s_save(head);
	}
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

/*查询所有学生信息*/
void s_show(struct student *head)
{
	
	struct student *p;
	p = head;
	while (p != NULL){
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

/*学生管理主页面*/
void s_menu()
{
	int num;
while(num<9){
	printf(" \n                    \n");
	printf("*********************学生管理功能菜单*************************       \n");
	printf("     *********************************************     \n");
	printf("     * 1.从文件中录入学生信息   * *  2.添加学生信息       *     \n");
	printf("     *********************************************     \n");
	printf("     * 3.按学号查询学生信息     * *  4.按姓名查询学生信息   *     \n");
	printf("     *********************************************     \n");
	printf("     * 5.按学号修改学生信息     * *  6.按姓名修改学生信息  *     \n");
	printf("     *********************************************     \n");
	printf("     * 7.删除学生信息           * *  8.查询所有学生信息      *    \n");
	printf("     ************************************************  \n");
	printf("     * 9.返回上一菜单           \n");
	printf("     *************************  \n");
	printf("     ----------------------   ----------------------   \n");
	printf("请选择菜单编号:");
	scanf("%d", &num);
	switch (num)
	{
		case 1:
			load_stu(); 
			break;
		case 2:
			s_insert(head);
			break;
		
		case 3:
			s_show_num(head);
			break;
		case 4:
			s_show_name(head);
			break;
		case 5:
			s_modify_num(head);
			break;
		case 6:
			s_modify_name(head);
			break;
		case 7:
			s_delete(head);
			break;
		case 8:
			s_show(head);
			break;

		case 9:
			printf("返回上一菜单!\n");
			break;
		default:printf("请在1-9之间选择\n");
	}
}
}
