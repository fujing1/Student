#define MAXN 50    //课程名最大长度
#define COU_F  "course.txt"  //文件存放路径及文件名

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

void load_cou();
struct course *find_cnum(struct course *c_head,int num);  //按课程号查找课程
struct course *load_cend(struct course *c_head);  //文件尾
void c_menu();                                 //主菜单
void c_insert(struct course *c_head);        //增加课程的函数
void c_show(struct course *c_head);       //根据课程号展示课程信息
void c_delete(struct course *c_head);        //删除课程的函数
void c_modify(struct course *c_head);       //修改课程信息
