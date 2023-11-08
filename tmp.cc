#include<string>
#include<vector>

// 模块
class ExamSystemApp {
    IDataBaseService  *db_service_; 
    Authentication authentic_; // 注入 db
    User user_; // 注入 db
};

// class ExamSystemView;

// Repository Module， 虚函数为菜单展示函数
class User {
    int user_id_;
    std::string user_name_;
    IDataBaseService  *db_service_; 
    User(IDataBaseService *);
}; 
class AdminService : User{
    ScheduleService schedule_service_;
    UserManagement  user_manage_service_;

};	/*	UserManagement;
    *	ScheduleService;
    *	
    */

//	QuestionBank PaperBank ScheduleService AnswerBank
class TeacherService : User {

    PaperBank paper_bank_service_;

};	
//	AnswerBank ScheduleService
class StudentService : User {
    AnswerBank answer_bank_service_;
};	

// student 定时答题用select做


class Authentication { // 登陆功能
    Authentication(IDataBaseService *);
    void Login();    
};

class ScheduleService {	/* Paper PaperBank 选取相应试卷
						* 查看考试安排，主动添加考试安排，教师提交考试安排请求，审议考试安排请求
                        *	提醒考试时间
                        */
    void ViewSchedule();
    void CommitScheduleRequest(Paper *);
    void CheckScheduleRequest();
    void RemindSchedule();

};
class UserManagement {	// 查看用户列表，增删改用户查用户
    void ViewUserList();
    void CreateUser();
    void FindUser();
    void UpdateUser();
    void DeleteUser();
};


class Question {
private:
    int question_id_;
    std::string quetion_context_;
    virtual void ShowQuestion(); 
};
class ChoiceQuestion : Question {
private:
    std::vector<std::string> question_choices_; 
    int question_answer_;
    void ShowQuestion() override;  
};
class JudgementQuestion : Question {
private:
    std::vector<std::string> question_judgement_; 
    int question_answer_;
    void ShowQuestion() override;  
};
class SubjectiveQuestion : Question {
private:
    std::string question_answer_;
    void ShowQuestion() override;  
};

// Question IDataBaseService	教师出题用，教师查看题库
class QuestionBank {
    void ViewQuestionList();
    Question CreateQuestion();
    void AddQuestion();
};	

class Paper;
// QuestionBank Paper IDataBaseService	教师出卷用
class PaperBank {
    void ViewQuestionList();
    Question CreateQuestion();
    void AddQuestion();
};
class Answer;
class AnswerBank;	// Answer IDataBaseService	学生答题用，教师改卷用，学生查看成绩用

class IDataBaseService { // 使用 Repository Module 解耦！使得后面可以从json换成redis！ CRUD
    virtual void CreateUser();
    virtual void FindUser();
    virtual void UpdateUser();
    virtual void DeleteUser();
};

class LogService;

class BackUpService;
// 工厂模式和Repository模式相比有什么不同？代码例子说明

