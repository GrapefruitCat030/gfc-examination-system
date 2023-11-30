#pragma once 

#include "question.h"
#include "database_service.h"
#include "log_service.h"


class IQuestionBankService {
public:
    virtual ~IQuestionBankService() {};
    virtual void        ViewQuestionList() = 0;
    virtual Question    CreateQuestion() = 0;
    virtual void        AddQuestion() = 0;
    virtual void        ChooseQuestion() = 0;
};
class QuestionBankService : public IQuestionBankService {
public:
    DataBaseService *db_service_; 
    LogService      *log_service_;
    std::vector<Question> question_list;
    std::vector<ChoiceQuestion> cq_list;
    std::vector<JudgementQuestion> jq_list;
    std::vector<SubjectiveQuestion> sq_list;

    QuestionBankService(DataBaseService *, LogService *);
    void        ViewQuestionList() override;
    Question    CreateQuestion() override;
    void        AddQuestion() override;
    void        ChooseQuestion() override;
};	
