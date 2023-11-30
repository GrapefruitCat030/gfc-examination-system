#pragma once 

#include "paper.h"
#include "database_service.h"
#include "log_service.h"

class IPaperBankService {
public:
    virtual ~IPaperBankService() {};
    virtual void        ViewPaperList() = 0;
    virtual void        ViewPaper() = 0;
    virtual void        AddPaper() = 0;
};
// QuestionBankService Paper DataBaseService	教师出卷用
class PaperBankService : public IPaperBankService {
public:
    DataBaseService *db_service_; 
    LogService      *log_service_;
    std::vector<Paper> paper_list;

    PaperBankService(DataBaseService *, LogService *);
    ~PaperBankService() override;
    void        ViewPaperList() override;
    void        ViewPaper() override;
    void        AddPaper() override;
};
