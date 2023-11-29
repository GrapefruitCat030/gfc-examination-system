#include "authentication.h"

#include<iostream>
#include<string>
#include<vector>

Authentication::Authentication(DataBaseService * db_service, LogService * log_service) {
    db_service_ = db_service;
    log_service_ = log_service;
}

User * Authentication::Login() {
    
    /* TODO */
    std::cout << "Welcome to the Exam System !\n"
                 "Please Login in !"
                << std::endl;   

    while(true) {

        std::string username, password;
        std::cout << "Enter your username: ";
        std::cin >> username;
        std::cout << "Enter your password: ";
        std::cin >> password;

        UserRecord record = db_service_->GetUserRecordByName(username);
        if(record.user_name_.empty()) {
            std::cout << "Cannot find the user." << std::endl;
            continue;
        }
        else {
            if(record.password_ != password) {
                std::cout << "Authentication Fail !" << std::endl;
                continue;
            }
            else {
                std::cout << "Authentication Success !" << std::endl;
            }
        }
        User *basic_user = new User (record.user_id_, record.user_name_, record.password_, record.authority_, db_service_, log_service_);
        return basic_user;
    }
}