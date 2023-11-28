#pragma once

class Authentication { // 登陆功能
public:    
    DataBaseService *db_service_; 
    LogService      *log_service_;
    Authentication(DataBaseService *, LogService *);

    int Login();    
};
