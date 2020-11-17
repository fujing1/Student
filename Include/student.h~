#define MAXN 50    //学生姓名，学号，课程名最大长度
#define STU_F  "student.txt"  //文件存放路径及文件名

struct student //学生信息结构体
{
 	int num;  //学号
	char name[MAXN];      //姓名
	int course_sum;  //选课总数
	int score_sel; //已选课总学分
	char course[50][MAXN];  //记录选课课程
	struct student *next;
};

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
