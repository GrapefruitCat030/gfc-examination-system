#pragma once

#include "database_service.h"
#include "log_service.h"
#include "user.h"

class Authentication { // 登陆功能
public:    
    DataBaseService *db_service_; 
    LogService      *log_service_;
    Authentication(DataBaseService *, LogService *);

    User & Login();    
};
