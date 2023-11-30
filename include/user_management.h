#pragma once 

#include "database_service.h"
#include "log_service.h"


// 查看用户列表，增删改用户查用户
class UserManagement {	
public:
    void ViewUserList();
    void AddUser();
    void FindUser();
    void DeleteUser();

    DataBaseService *db_service_; 
    LogService      *log_service_;
    UserManagement(DataBaseService *, LogService *);
};

