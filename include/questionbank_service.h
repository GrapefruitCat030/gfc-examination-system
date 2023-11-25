#pragma once 

class IQuestionBankService {
    virtual void        ViewQuestionList();
    virtual Question    CreateQuestion();
    virtual void        AddQuestion();
    virtual void        ChooseQuestion();
};
class QuestionBankService : IQuestionBankService {
    DataBaseService &db_service_; 
    LogService      &log_service_;
    QuestionBankService(DataBaseService &, LogService &);
    
    void        ViewQuestionList();
    Question    CreateQuestion();
    void        AddQuestion();
    void        ChooseQuestion();
};	
