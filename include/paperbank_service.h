#pragma once 

#include "paper.h"
#include "database_service.h"
#include "log_service.h"

class IPaperBankService {
public:
    virtual void        ViewPaperList() {};
    // 创建试卷实例，每次添加试题先进vector，最后再加到两张表中
    virtual Paper       CreatePaper() {};
    virtual void        AddPaper() {};
};
// QuestionBankService Paper DataBaseService	教师出卷用
class PaperBankService : public IPaperBankService {
public:
    DataBaseService *db_service_; 
    LogService      *log_service_;
    PaperBankService(DataBaseService *, LogService *);

    void        ViewPaperList() override;
    Paper       CreatePaper() override;
    void        AddPaper() override;
};
