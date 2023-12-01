#pragma once

#include "answer.h"
#include "database_service.h"
#include "log_service.h"

class IAnswerBankServiceTeacher {
public:
    virtual ~IAnswerBankServiceTeacher() {};
    virtual void ViewAnswerList(){};
    virtual void CorrectAnswer(){};
};
class IAnswerBankServiceStudent {
public:
    virtual ~IAnswerBankServiceStudent() {};
    virtual void StartAnswer(){};
    virtual void ViewResult() {};
};
class AnswerBankService : public IAnswerBankServiceTeacher, public IAnswerBankServiceStudent {
public:
    DataBaseService *db_service_; 
    LogService      *log_service_;
    std::vector<Answer> answer_list_;
    std::vector<AnswerSheet> answer_sheet_list_;

    AnswerBankService(DataBaseService *, LogService *);

    // Teacher Interface
    void ViewAnswerList() override;
    void CorrectAnswer() override;
    // Student Interface
    void StartAnswer() override;
    void ViewResult() override;
};	
