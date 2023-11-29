#include "user.h"

#include<iostream>
#include<limits>


User::User() {

}
User::User(int id, std::string name, std::string pwd, int auth, DataBaseService *dbs, LogService *lgs) : 
            user_id_(id), user_name_(name), password_(pwd), authority_(auth), db_service_(dbs), log_service_(lgs){

}

User::~User() {

}

Admin::Admin(User *base, DataBaseService *dbs, LogService *lgs) :   User(*base), 
                                                        user_manage_service_(dbs, lgs) {
    // ScheduleService tmp1 = ScheduleService(dbs, lgs);
    schedule_service_ = new ScheduleService(dbs, lgs);
}

void Admin::BootService() {

    while(true) {
        std::cout << "This is Admin Menu.\n"
                    "Choose your service: 1.User Management 2.Schedule Service\n"
                    ">>> "
                    ;
        std::string input;
        std::cin >> input;  // 获取并返回第一个字符
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 清除输入缓冲区
        std::cout << std::endl;
        /* Choose Service */
        // std::cout << input[0];
        int rc = (input[0]) - '0';
        if(rc == 1) {
            UserMangeMenu();
        }
        else if (rc == 2) {
            ScheduleMenu();
        }
        else exit(-1);
    }
}
void Admin::UserMangeMenu() {
    while(true) {
        std::cout << "This is User Management Menu.\n"
                    "Choose your service:\n"
                    "1.View All 2.Find User 3.Add User 4.Delete User\n"
                    ">>> "
                    ;
        std::string input;
        std::cin >> input;  // 获取并返回第一个字符
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 清除输入缓冲区
        std::cout << std::endl;
        
        /* Choose Service */
        int rc = (input[0]) - '0';
        // std::cout << input[0];
        if(rc == 1) {
            user_manage_service_.ViewUserList();
        }
        else if (rc == 2) {
            user_manage_service_.FindUser();
        }
        else if(rc == 3) {
            user_manage_service_.AddUser();
        }
        else if(rc == 4) {
            user_manage_service_.DeleteUser();
        }
        else return;
    }
}
void Admin::ScheduleMenu() {
    while(true) {
        std::cout <<    "This is Schedule Menu.\n"
                        "Choose your service:\n"
                        "1.View All 2.Add Schedule 3.Check Request 4.Set Request\n"
                        ">>> "
                        ;
        std::string input;
        std::cin >> input;  // 获取并返回第一个字符
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 清除输入缓冲区
        std::cout << std::endl;

        /* Choose Service */
        int rc = (input[0]) - '0';
        // std::cout << input[0];
        if(rc == 1) {
            schedule_service_->ViewSchedule();
        }
        else if (rc == 2) {
            schedule_service_->AddSchedule();
        }
        else if(rc == 3) {
            schedule_service_->CheckScheduleRequest();
        }
        else if(rc == 4) {
            schedule_service_->ChooseAndSetRequest();
        }
        else return;
    }
}





Teacher::Teacher(User *base, DataBaseService *dbs, LogService *lgs, CourseType t) :   User(*base) {
    schedule_service_ = new ScheduleService(dbs, lgs);
    question_bank_service_ = new QuestionBankService(dbs, lgs);
    paper_bank_service_ = new PaperBankService(dbs, lgs);
    answer_bank_service_ = new AnswerBankService(dbs, lgs);

}
void Teacher::BootService() {

    while(true) {
        std::cout << "This is Admin Menu.\n"
                    "Choose your service: 1.User Management 2.Schedule Service\n"
                    ">>> "
                    ;
        std::string input;
        std::cin >> input;  // 获取并返回第一个字符
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 清除输入缓冲区
        std::cout << std::endl;
        /* Choose Service */
        // std::cout << input[0];
        int rc = (input[0]) - '0';
        if(rc == 1) {
            ScheduleMenu();
        }
        else if (rc == 2) {
            QuestionBankMenu();
        }
        else if(rc == 3) PaperBankMenu();
        else if(rc == 4) AnswerBankMenu();
        else return;
    }
}

void Teacher::ScheduleMenu() {}
void Teacher::QuestionBankMenu() {}
void Teacher::PaperBankMenu() {}
void Teacher::AnswerBankMenu() {}






Student::Student(User *base, DataBaseService *dbs, LogService *lgs) : User(*base) {

}
void Student::BootService() {

    while(true) {
        std::cout << "This is Admin Menu.\n"
                    "Choose your service: 1.User Management 2.Schedule Service\n"
                    ">>> "
                    ;
        std::string input;
        std::cin >> input;  // 获取并返回第一个字符
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 清除输入缓冲区
        std::cout << std::endl;
        /* Choose Service */
        // std::cout << input[0];
        int rc = (input[0]) - '0';
        if(rc == 1) {
        }
        else if (rc == 2) {
        }
        else return;
    }
}

void Student::ScheduleMenu() {}
void Student::AnswerBankMenu() {}


















