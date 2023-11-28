#pragma once

#include<string>


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
    Admin(DataBaseService &, LogService &);
};
class Teacher : User {
    CourseType course_;

    IScheduleServiceTeacher schedule_service_;
    IQuestionBankService question_bank_service_;
    IPaperBankService paper_bank_service_;
    IAnswerBankServiceTeacher answer_bank_service_;

    Teacher(DataBaseService &, LogService &);
};	
class Student : User {
    IScheduleServiceStudent schedule_service_;
    IAnswerBankServiceStudent answer_bank_service_;

    Student(DataBaseService &, LogService &);
};	
