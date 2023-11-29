#include "user_management.h"

#include"user.h"
#include<iostream>

UserManagement::UserManagement(DataBaseService *dbs, LogService *lgs) :
                db_service_(dbs), log_service_(lgs) {
} 

void UserManagement::ViewUserList() {
    std::vector<UserRecord>  user_records = db_service_->GetAllUserRecord();
    for(auto record: user_records) {
        std::cout   << record.user_id_ << " "\
                    << record.user_name_ << " "\
                    << record.authority_ << " "\
                    << std::endl;
    }
    std::cout << std::endl;
} 

void UserManagement::AddUser() {
    
    std::string id, name, password, authority;

    std::cout << "Enter id: ";
    std::cin >> id;
    std::cout << "Enter username: ";
    std::cin >> name;
    std::cout << "Enter password: ";
    std::cin >> password;
    std::cout << "Enter authority: ";
    std::cin >> authority;

    UserRecord tmp = {std::stoi(id), name, password, std::stoi(authority)};
    db_service_->AddUser(tmp, false);
}
void UserManagement::FindUser() {
    std::cout << "Enter target username: ";
    std::string name;
    std::cin >> name;
    UserRecord record = db_service_->GetUserRecordByName(name);
    if(record.user_name_.empty()) {
            std::cout << "Cannot find the user." << std::endl;
            
    }
    else {
        std::cout   << record.user_id_ << " "\
                    << record.user_name_ << " "\
                    << record.authority_ << " "\
                    << std::endl;
    }
}
void UserManagement::UpdateUser() {

}
void UserManagement::DeleteUser() {

} 

