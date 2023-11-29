#pragma once 

#include "question.h"
#include "database_service.h"
#include "log_service.h"


class IQuestionBankService {
public:
    virtual void        ViewQuestionList() {};
    virtual Question    CreateQuestion(){};
    virtual void        AddQuestion(){};
    virtual void        ChooseQuestion(){};
};
class QuestionBankService : public IQuestionBankService {
public:
    DataBaseService *db_service_; 
    LogService      *log_service_;
    QuestionBankService(DataBaseService *, LogService *);
    
    void        ViewQuestionList() override;
    Question    CreateQuestion() override;
    void        AddQuestion() override;
    void        ChooseQuestion() override;
};	
