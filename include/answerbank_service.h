#pragma once

#include "answer.h"

// Teacher Interface: 改卷
class IAnswerBankServiceTeacher {
    virtual void ViewAnswerList();
    virtual void ChooseAnswer();
    virtual void CorrectAnswer();
};
// Student Interface: 答卷，查看成绩
class IAnswerBankServiceStudent {
    virtual void StartAnswer();
    virtual AnswerSheet ViewResult();
};
class AnswerBankService : IAnswerBankServiceTeacher, IAnswerBankServiceStudent {
    DataBaseService &db_service_; 
    LogService      &log_service_;
    AnswerBankService(DataBaseService &, LogService &);

    // Teacher Interface
    void ViewAnswerList() override;
    void ChooseAnswer() override;
    void CorrectAnswer() override;
    // Student Interface
    void StartAnswer() override;
    AnswerSheet ViewResult() override;
};	
