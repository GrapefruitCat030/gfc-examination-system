#include<string>
#include<vector>
#include<array>
#include<variant>
#include<memory>

enum CourseType {
   kSubjectPython = 0,
   kSubjectCpp, 
};

enum QuestionType {
    kQuestionTypeChoice = 0,
    kQuestionTypeJudge,
    kQuestionTypeSubject,
};

// 依赖注入模式
class ExamSystemService {
public:
    DataBaseService &db_service_; 
    LogService      &log_service_;
    Authentication authentic_; // 注入 db
    User user_; // 注入 db

    ExamSystemService(DataBaseService &, LogService &);

};

// class ExamSystemView;

// Repository Module， 虚函数为菜单展示函数
class User {
public:
    int user_id_;
    std::string user_name_;
    std::string password_;
    int authority_;

    DataBaseService    &db_service_; 
    LogService          &log_service_;
    
    User(DataBaseService &, LogService &);
}; 

class Admin : User {
    UserManagement          user_manage_service_;
    IScheduleServiceAdmin   schedule_service_;
};
class Teacher : User {
    CourseType course_;

    IScheduleServiceTeacher schedule_service_;
    IQuestionBankService question_bank_service_;
    IPaperBankService paper_bank_service_;
    IAnswerBankServiceTeacher answer_bank_service_;
};	
class Student : User {
    IScheduleServiceStudent schedule_service_;
    IAnswerBankServiceStudent answer_bank_service_;
};	

// student 定时答题用select做


class Authentication { // 登陆功能
    DataBaseService &db_service_; 
    LogService      &log_service_;
    Authentication(DataBaseService &, LogService &);

    void Login();    
};

class Schedule {
    int         schedule_id_;
    std::string schedule_date_;
    std::string time_begin_;
    std::string time_end_;
    CourseType  course_;
    int         paper_id_;
    bool        request_flag_;
    
    void set_request_flag(bool);
};
// Admin Interface
class IScheduleServiceAdmin {
    virtual void CheckScheduleRequest();
    virtual void ChooseAndSetRequest();
    virtual void AddSchedule();
    virtual void ViewSchedule();
}; 
// Teacher Interface
class IScheduleServiceTeacher {
    virtual void CommitScheduleRequest();
    virtual void ViewSchedule();
}; 
// Student Interface
class IScheduleServiceStudent {
    virtual void RemindSchedule();
    virtual void ViewSchedule();
}; 
// 查看考试安排，主动添加考试安排，教师提交考试安排请求，审议考试安排请求
class ScheduleService : IScheduleServiceAdmin, IScheduleServiceTeacher, IScheduleServiceStudent {	
public:
    DataBaseService &db_service_; 
    LogService      &log_service_;
    std::vector<Schedule> schedule_list_;

    ScheduleService(DataBaseService &, LogService &);
    void ViewSchedule();
    // Admin Interface
    void CheckScheduleRequest() override;
    void ChooseAndSetRequest() override;
    void AddSchedule() override;
    // Teacher Interface
    void CommitScheduleRequest() override;
    // Student Interface
    void RemindSchedule() override;
};

// 查看用户列表，增删改用户查用户
class UserManagement {	
    void ViewUserList();
    void CreateItem();
    void FindItem();
    void UpdateItem();
    void DeleteItem();

    DataBaseService &db_service_; 
    LogService      &log_service_;
    UserManagement(DataBaseService &, LogService &);
};




// Question Interface
class Question {
private:
    int             question_id_;
    CourseType      course_;    
    QuestionType    type_;
    std::string     quetion_context_;
    int             mark_;
    
    virtual void ShowQuestion(); 
};
class ChoiceQuestion : Question {
private:
    std::array<std::string, 4> question_choices_; 
    int                        question_answer_;
    
    void ShowQuestion() override;  
};
class JudgementQuestion : Question {
private:
    bool question_answer_;
    void ShowQuestion() override;  
};
class SubjectiveQuestion : Question {
private:
    std::string question_answer_;
    void ShowQuestion() override;  
};
class IQuestionBankService {
    virtual void        ViewQuestionList();
    virtual Question    CreateQuestion();
    virtual void        AddQuestion();
    virtual void        ChooseQuestion();
};
class QuestionBankService : IQuestionBankService {
    DataBaseService &db_service_; 
    LogService      &log_service_;
    QuestionBankService(DataBaseService &, LogService &);
    
    void        ViewQuestionList();
    Question    CreateQuestion();
    void        AddQuestion();
    void        ChooseQuestion();
};	




class Paper {
    int         paper_id_;
    CourseType  course_;    
    std::string paper_name_;
    int         total_mark_;
    std::vector<int> question_id_list_;
    void ShowPaper();
};
class IPaperBankService {
    virtual void        ViewPaperList();
    // 创建试卷实例，每次添加试题先进vector，最后再加到两张表中
    virtual Paper       CreatePaper();
    virtual void        AddPaper();
};
// QuestionBankService Paper DataBaseService	教师出卷用
class PaperBankService : IPaperBankService {
    DataBaseService &db_service_; 
    LogService      &log_service_;
    PaperBankService(DataBaseService &, LogService &);

    void        ViewPaperList();
    Paper       CreatePaper();
    void        AddPaper();
};




class Answer {
    int answer_id_;
    int question_id_;
    std::variant<int, bool, std::string> answer_context_;
    int mark_;
};
class AnswerSheet {
    int answer_sheet_id_;
    int paper_id_;
    int student_id_;
    int total_mark_;
    std::vector<Answer> answer_list_;
    
    void ShowAnswerSheet();
};
/* 依赖反转原则，接口隔离原则 */

// Teacher Interface: 改卷
class IAnswerBankServiceTeacher {
    virtual void ViewAnswerList();
    virtual void ChooseAnswer();
    virtual void CorrectAnswer();
};
// Student Interface: 答卷，查看成绩
class IAnswerBankServiceStudent {
    virtual void StartAnswer();
    virtual AnswerSheet ViewResult();
};
class AnswerBankService : IAnswerBankServiceTeacher, IAnswerBankServiceStudent {
    DataBaseService &db_service_; 
    LogService      &log_service_;
    AnswerBankService(DataBaseService &, LogService &);

    // Teacher Interface
    void ViewAnswerList() override;
    void ChooseAnswer() override;
    void CorrectAnswer() override;
    // Student Interface
    void StartAnswer() override;
    AnswerSheet ViewResult() override;
};	



// 数据库服务类使用Repository模式
class DataBaseService {
private:
    std::unique_ptr<IDataBaseRepository> userRepository;

public:
    void SetUserRepository(std::unique_ptr<IDataBaseRepository> repository) {
        userRepository = std::move(repository);
    }

    void Connect() {
        // 连接数据库的逻辑
    }

    void Disconnect() {
        // 断开数据库连接的逻辑
    }

    void CreateItem() {
        userRepository->CreateItem();
    }

    void FindItem() {
        userRepository->FindItem();
    }

    void UpdateItem() {
        userRepository->UpdateItem();
    }

    void DeleteItem() {
        userRepository->DeleteItem();
    }
};
class IDataBaseRepository {
public:
    virtual void CreateItem() = 0;
    virtual void FindItem() = 0;
    virtual void UpdateItem() = 0;
    virtual void DeleteItem() = 0;
};

// 实现具体的数据库访问逻辑
class JsonDBRepository : public IDataBaseRepository {
public:
    void CreateItem() override {
        // 在JSON存储中创建用户的逻辑
    }

    void FindItem() override {
        // 在JSON存储中查找用户的逻辑
    }

    void UpdateItem() override {
        // 在JSON存储中更新用户的逻辑
    }

    void DeleteItem() override {
        // 在JSON存储中删除用户的逻辑
    }
};

class RedisDBRepository : public IDataBaseRepository {
public:
    void CreateItem() override {
        // 在Redis存储中创建用户的逻辑
    }

    void FindItem() override {
        // 在Redis存储中查找用户的逻辑
    }

    void UpdateItem() override {
        // 在Redis存储中更新用户的逻辑
    }

    void DeleteItem() override {
        // 在Redis存储中删除用户的逻辑
    }
};

// 单例模式
class LogService {
	void WriteLog();
};

class BackUpService;

int main() {

}