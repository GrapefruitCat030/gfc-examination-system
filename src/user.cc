#include "user.h"

#include<iostream>

User::User(int id, std::string name, std::string pwd, int auth, DataBaseService *dbs, LogService *lgs) : 
            user_id_(id), user_name_(name), password_(pwd), authority_(auth), db_service_(dbs), log_service_(lgs){

}

Admin::Admin(const User &base, DataBaseService *dbs, LogService *lgs) :   User(base), 
                                                        user_manage_service_(dbs, lgs) {
    ScheduleService tmp1 = ScheduleService(dbs, lgs);
    schedule_service_ = &tmp1;
}

void Admin::BootService() {

    std::cout << "This is Admin Menu.\n"
                 "Choose your service: 1.User Management 2.Schedule Service\n"
                 ">>> "
                ;
    char input_ch;
    std::cin.get(input_ch);  // 获取并返回第一个字符
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 清除输入缓冲区

    /* Choose Service */
    int rc = input_ch - '0';
    if(rc == 0) {
        UserMangeMenu();
    }
    else if (rc == 1) {
        ScheduleMenu();
    }
    else exit(-1);
}
void Admin::UserMangeMenu() {

}
void Admin::ScheduleMenu() {

}








// Teacher::Teacher(DataBaseService *dbs, LogService *lgs, CourseType t) :   User(dbs, lgs) {
//     schedule_service_ = &ScheduleService(dbs, lgs);
//     // question_bank_service_ = &QuestionBankService(dbs, lgs);
//     // PaperBankService = &PaperBankService(dbs, lgs);
//     // AnswerBankService = &AnswerBankService(dbs, lgs);
// }


























