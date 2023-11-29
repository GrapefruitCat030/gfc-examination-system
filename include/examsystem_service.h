#pragma once

#include "database_service.h"
#include "log_service.h"
#include "authentication.h"
#include "user.h"

// 依赖注入模式
class ExamSystemService {
public:
    DataBaseService *db_service_; 
    LogService      *log_service_;
    User            *user_; // 注入 db
    Authentication  authentic_; // 注入 db

    ExamSystemService(DataBaseService *, LogService *);
    void BootService();
};