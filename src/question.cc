#include "question.h"
#include "constant.h"

#include<iostream>

ChoiceQuestion::ChoiceQuestion(const Question &base) : Question(base){

}


JudgementQuestion::JudgementQuestion(const Question &base) : Question(base){

}

SubjectiveQuestion::SubjectiveQuestion(const Question &base) : Question(base){

}


void Question::ShowQuestion() {
    std::cout   << question_id_ << "\t"
                << course_ << "\t"
                << QuestionTypeStr[type_] << "\t"
                << quetion_context_ << "\t"
                << mark_ 
                << std::endl;
} 


void ChoiceQuestion::ShowQuestion() {

} 
void JudgementQuestion::ShowQuestion() {

} 
void SubjectiveQuestion::ShowQuestion() {

} 

