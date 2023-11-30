#pragma once

#include<array>
#include<string>

#include<constant.h>

// Question Interface
class Question {
public:
    int             question_id_;
    std::string     course_;    
    QuestionType    type_;
    std::string     quetion_context_;
    int             mark_;
    
    Question() {};
    ~Question() {};
    virtual void ShowQuestionDetail(); 
};
class ChoiceQuestion : public Question {
public:
    std::array<std::string, 4> question_choices_; 
    int                        question_answer_;
    
    ChoiceQuestion(const Question &);
    void ShowQuestionDetail() override;  
    void ShowQuestionOnly();
};
class JudgementQuestion : public Question {
public:
    bool question_answer_;
    JudgementQuestion(const Question &);
    void ShowQuestionDetail() override;  
    void ShowQuestionOnly();
};
class SubjectiveQuestion : public Question {
public:
    std::string question_answer_;
    SubjectiveQuestion(const Question &);
    void ShowQuestionDetail() override;  
    void ShowQuestionOnly();
};