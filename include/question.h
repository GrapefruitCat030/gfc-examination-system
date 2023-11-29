#pragma once

#include<array>
#include<string>

#include<constant.h>

// Question Interface
class Question {
private:
    int             question_id_;
    CourseType      course_;    
    QuestionType    type_;
    std::string     quetion_context_;
    int             mark_;
    
    virtual void ShowQuestion(); 
};
class ChoiceQuestion : Question {
private:
    std::array<std::string, 4> question_choices_; 
    int                        question_answer_;
    
    void ShowQuestion() override;  
};
class JudgementQuestion : Question {
private:
    bool question_answer_;
    void ShowQuestion() override;  
};
class SubjectiveQuestion : Question {
private:
    std::string question_answer_;
    void ShowQuestion() override;  
};