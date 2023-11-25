#pragma once 

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

