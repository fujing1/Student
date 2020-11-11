#define MAXN 50    //学生姓名，学好，课程名最大长度

struct student //学生信息结构体
{
	char name[MAXN];      //姓名
 	char num[MAXN];  //学号
	double score_sel = 0; //已选课总学分
	char course[50][MAXN];  //记录选课课程的编号
};