#pragma once

class Authentication { // 登陆功能
    DataBaseService &db_service_; 
    LogService      &log_service_;
    Authentication(DataBaseService &, LogService &);

    void Login();    
};
