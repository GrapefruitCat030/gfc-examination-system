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
Admin::~Admin() {
    delete schedule_service_;
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
        if(rc == 1)      user_manage_service_.ViewUserList();
        else if(rc == 2) user_manage_service_.FindUser();
        else if(rc == 3) user_manage_service_.AddUser();
        else if(rc == 4) user_manage_service_.DeleteUser();
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





Teacher::Teacher(User *base, DataBaseService *dbs, LogService *lgs) :   User(*base) {
    schedule_service_ = new ScheduleService(dbs, lgs);
    question_bank_service_ = new QuestionBankService(dbs, lgs);
    paper_bank_service_ = new PaperBankService(dbs, lgs);
    answer_bank_service_ = new AnswerBankService(dbs, lgs);

}
Teacher::~Teacher() {
    delete schedule_service_;
    delete question_bank_service_;
    delete paper_bank_service_;
    delete answer_bank_service_;
}
void Teacher::BootService() {
    while(true) {
        std::cout << "This is Teacher Menu.\n"
                    "Choose your service:\n"
                    "1.Schedule Service 2.Question Bank 3.Paper Bank 4.Answer Bnak\n"
                    ">>> "
                    ;
        std::string input;
        std::cin >> input;  // 获取并返回第一个字符
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 清除输入缓冲区
        std::cout << std::endl;
        /* Choose Service */
        int rc = (input[0]) - '0';
        if(rc == 1)      ScheduleMenu();
        else if(rc == 2) QuestionBankMenu();
        else if(rc == 3) PaperBankMenu();
        else if(rc == 4) AnswerBankMenu();
        else return;
    }
}
void Teacher::ScheduleMenu() {
    while(true) {
        std::cout << "This is Schedule Menu.\n"
                     "Choose your service:\n"
                     "1.View All 2.Commit Schedule Request\n"
                     ">>> "
                     ;
        std::string input;
        std::cin >> input;  // 获取并返回第一个字符
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 清除输入缓冲区
        std::cout << std::endl;
        
        /* Choose Service */
        int rc = (input[0]) - '0';
        if(rc == 1)      schedule_service_->ViewSchedule();
        else if(rc == 2) schedule_service_->CommitScheduleRequest();
        else return;
    }
}
void Teacher::QuestionBankMenu() {
    while(true) {
        std::cout << "This is Question Bank Menu.\n"
                     "Choose your service:\n"
                     "1.View All 2.Choose One 3.Create Question\n"
                     ">>> "
                     ;
        std::string input;
        std::cin >> input;  // 获取并返回第一个字符
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 清除输入缓冲区
        std::cout << std::endl;
        
        /* Choose Service */
        int rc = (input[0]) - '0';
        if(rc == 1)      question_bank_service_->ViewQuestionList();
        else if(rc == 2) question_bank_service_->ChooseQuestion();
        else if(rc == 3) question_bank_service_->CreateQuestion();
        else return;
    }
}
void Teacher::PaperBankMenu() {
    while(true) {
        std::cout << "This is Paper Bank Menu.\n"
                     "Choose your service:\n"
                     "1.View All 2.Create Question\n"
                     ">>> "
                     ;
        std::string input;
        std::cin >> input;  // 获取并返回第一个字符
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 清除输入缓冲区
        std::cout << std::endl;
        
        /* Choose Service */
        int rc = (input[0]) - '0';
        if(rc == 1)      paper_bank_service_->ViewPaperList();
        else if(rc == 2) paper_bank_service_->CreatePaper();
        else return;
    }
}
void Teacher::AnswerBankMenu() {
    while(true) {
        std::cout << "This is Answer Bank Menu.\n"
                     "Choose your service:\n"
                     "1.View All 2.Choose And Correct\n"
                     ">>> "
                     ;
        std::string input;
        std::cin >> input;  // 获取并返回第一个字符
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 清除输入缓冲区
        std::cout << std::endl;
        
        /* Choose Service */
        int rc = (input[0]) - '0';
        if(rc == 1)      answer_bank_service_->ViewAnswerList();
        else if(rc == 2) answer_bank_service_->ChooseAnswer();
        else return;
    }
}






Student::Student(User *base, DataBaseService *dbs, LogService *lgs) : User(*base) {
    schedule_service_ = new ScheduleService(dbs, lgs);
    answer_bank_service_ = new AnswerBankService(dbs, lgs);
}
Student::~Student() {
    delete schedule_service_;
    delete answer_bank_service_;
}
void Student::BootService() {
    while(true) {
        std::cout << "This is Student Menu.\n"
                    "Choose your service: 1.Schedule Service 2.Answer Bank\n"
                    ">>> "
                    ;
        std::string input;
        std::cin >> input;  // 获取并返回第一个字符
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 清除输入缓冲区
        std::cout << std::endl;
        /* Choose Service */
        // std::cout << input[0];
        int rc = (input[0]) - '0';
        if(rc == 1) ScheduleMenu();
        else if (rc == 2) AnswerBankMenu();
        else return;
    }
}
void Student::ScheduleMenu() {
        std::cout << "This is Schedule Menu.\n"
                    << std::endl;
                     ;
        schedule_service_->ViewSchedule();
        schedule_service_->RemindSchedule();
        std::cout <<"\n"
                    "Press any key return.\n"
                    << std::endl;
                     ;
        getchar();
}
void Student::AnswerBankMenu() {}


















