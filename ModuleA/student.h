#define MAXN 50    //学生姓名，学好，课程名最大长度
#define STU_F  "/home/fujing/Student/ModuleA/student.txt"  //文件存放路径及文件名

struct student //学生信息结构体
{
 	int num;  //学号
	char name[MAXN];      //姓名
	int course_sum;  //选课总数
	int score_sel; //已选课总学分
	char course[50][MAXN];  //记录选课课程
	struct student *next;
};

struct student* load_stu();
void menu();                                 //主菜单
void s_insert(struct student *head);        //增加学生的函数
void s_show_num(struct student *head);       //根据学号展示学生信息
void s_delete(struct student *head);        //删除学生的函数
void s_earch_stu(struct student *head);     //搜索学生的函数
void s_modify(struct student *head);       //管理员修改学生信息
