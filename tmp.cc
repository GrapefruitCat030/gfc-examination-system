#include<string>

// 模块
class ExamSystemApp;

// class ExamSystemView;

class User; // Repository Module， 虚函数为菜单展示函数
class AdminService;	/*	UserManagement;
					*	ScheduleService;
					*	
					*/
class TeacherService;	//	QuestionBank PaperBank ScheduleService AnswerBank
class StudentService;	//	AnswerBank ScheduleService

// student 定时答题用select做


class Authentication { // 登陆功能
    
};

class ScheduleService {	/* Paper PaperBank 选取相应试卷
						* 查看考试安排，主动添加考试安排，教师提交考试安排请求，审议考试安排请求
                        *	提醒考试时间
                        */
    void ShowSchedule();
    void CommitScheduleRequest(Paper *);
    void CheckScheduleRequest();
    void RemindSchedule();

};
class UserManagement {	// 查看用户列表，增删改用户查用户
    void ViewUserList();
    void CreateUser();
    void FindUserName(std::string);
    void FindUserId(int);
    void UpdateUser();
    void DeleteUser(int id);
};


class Question;
class QuestionBank;	// Question DataBaseService	教师出题用，教师查看题库
class Paper;
class PaperBank;	// QuestionBank Paper DataBaseService	教师出卷用
class Answer;
class AnswerBank;	// Answer DataBaseService	学生答题用，教师改卷用，学生查看成绩用

class DataBaseService { // 使用 Repository Module 解耦！使得后面可以从json换成redis！ CRUD
    virtual void CreateUser();
    virtual void FindUser();
    virtual void UpdateUser();
    virtual void DeleteUser();
};

class LogService;

class BackUpService;
// 工厂模式和Repository模式相比有什么不同？代码例子说明

