#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 50    //学生姓名，学号，课程名最大长度
#define COU_F  "/home/fujing/Student/ModuleB/course.txt"  //文件存放路径及文件名
#define STU_F  "/home/fujing/Student/ModuleA/student.txt"  //文件存放路径及文件名


struct course //课程信息结构体
{
 	int c_num;  //课程号
	char c_name[MAXN];      //课程名称
	char type[MAXN];      //课程性质
	int time;       //学时
	int stu_num;  //课程已选人数
	int score; //学分
	int limit;  //课程人数上线
	struct course *next;
};

struct student //学生信息结构体
{
 	int num;  //学号
	char name[MAXN];      //姓名
	int course_sum;  //选课总数
	int score_sel; //已选课总学分
	char course[50][MAXN];  //记录选课课程
	struct student *next;
};

int N;
int N1;
struct student *head;
struct course *c_head;

//课程所用函数
void load_cou();
struct course *find_cnum(struct course *c_head,int num);  //按课程号查找课程
struct course *load_cend(struct course *c_head);  //文件尾
void c_menu();                                 //主菜单
void c_insert(struct course *c_head);        //增加课程的函数
void c_show(struct course *c_head);       //根据课程号展示课程信息
void c_delete(struct course *c_head);        //删除课程的函数
void c_modify(struct course *c_head);       //修改课程信息

//学生管理所用函数
void load_stu();
struct student *load_end(struct student *head);    //文件尾
struct student *find_num(struct student *head,int num);  //根据学号查询
struct student *find_name(struct student *head,char name[]);  //根据姓名查询
void s_menu();                                 //主菜单
void s_insert(struct student *head);        //增加学生的函数
void s_show_num(struct student *head);       //根据学号展示学生信息
void s_show_name(struct student *head);       //根据姓名展示学生信息
void s_show(struct student *head);       //展示所有学生信息
void s_delete(struct student *head);        //删除学生的函数
void s_modify_num(struct student *head);       //根据学号修改学生信息
void s_modify_name(struct student *head);       //根据姓名修改学生信息
