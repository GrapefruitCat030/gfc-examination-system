#pragma once

#include "constant.h"
#include "database_service.h"
#include "log_service.h"
#include "user_management.h"
#include "schedule_service.h"
#include "questionbank_service.h"
#include "paperbank_service.h"
#include "answerbank_service.h"

#include<string>

// Repository Module， 虚函数为菜单展示函数
class User {
public:
    int user_id_;
    std::string user_name_;
    std::string password_;
    int authority_;

    DataBaseService   *db_service_; 
    LogService        *log_service_;

    User(int, std::string, std::string, int, DataBaseService *, LogService *);
    virtual void BootService();
}; 

class Admin : public User {
public:
    UserManagement          user_manage_service_;
    IScheduleServiceAdmin   *schedule_service_;
    
    Admin(const User& base, DataBaseService *, LogService *);
    void BootService() override;
    void UserMangeMenu();
    void ScheduleMenu();

};
class Teacher : public User {
public:
    CourseType course_;

    IScheduleServiceTeacher *schedule_service_;
    IQuestionBankService    *question_bank_service_;
    IPaperBankService       *paper_bank_service_;
    IAnswerBankServiceTeacher *answer_bank_service_;

    Teacher(DataBaseService *, LogService *, CourseType);
};	
class Student : public User {
public:
    IScheduleServiceStudent schedule_service_;
    IAnswerBankServiceStudent answer_bank_service_;

    Student(DataBaseService *, LogService *);
};	
