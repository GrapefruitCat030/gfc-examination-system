#include "authentication.h"

#include<iostream>
#include<string>
#include<vector>

User & Authentication::Login() {
    
    /* TODO */
    // db_service_->FindItem();
    std::string username, password;
    std::cout << "Enter your username: ";
    std::cin >> username;
    std::cout << "Enter your password: ";
    std::cin >> password;

    UserRecord record = db_service_->GetUserRecordByName(username);
    if(record.user_name_.empty()) {
        std::cout << "Cannot find the user." << std::endl;
        exit(-1);
    }
    else {
        if(record.password_ != password) {
            std::cout << "Authentication Fail !" << std::endl;
            exit(-1);
        }
        else {
            std::cout << "Authentication Success !" << std::endl;
        }
    }
    User basic_user(record.user_id_, record.user_name_, record.password_, record.authority_, db_service_, log_service_);
    return basic_user;
}