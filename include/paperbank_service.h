#pragma once 

#include "paper.h"
#include "database_service.h"
#include "log_service.h"

class IPaperBankService {
public:
    virtual ~IPaperBankService() {};
    virtual void        ViewPaperList() = 0;
    // 创建试卷实例，每次添加试题先进vector，最后再加到两张表中
    virtual Paper       CreatePaper() = 0;
    virtual void        AddPaper() = 0;
};
// QuestionBankService Paper DataBaseService	教师出卷用
class PaperBankService : public IPaperBankService {
public:
    DataBaseService *db_service_; 
    LogService      *log_service_;
    PaperBankService(DataBaseService *, LogService *);
    ~PaperBankService() override;
    void        ViewPaperList() override;
    Paper       CreatePaper() override;
    void        AddPaper() override;
};
