#include "question.h"
#include "constant.h"

#include<iostream>

ChoiceQuestion::ChoiceQuestion(const Question &base) : Question(base){

}


JudgementQuestion::JudgementQuestion(const Question &base) : Question(base){

}

SubjectiveQuestion::SubjectiveQuestion(const Question &base) : Question(base){

}


void Question::ShowQuestionDetail() {
    std::cout   << question_id_ << "\t"
                << course_ << "\t"
                << QuestionTypeStr[type_] << "\t"
                << mark_ 
                << std::endl;
} 


void ChoiceQuestion::ShowQuestionDetail() {
    std::cout   << question_id_ << "\t"
                << course_ << "\t"
                << QuestionTypeStr[type_] << "\t"
                << mark_ 
                << std::endl;
    std::cout   << "Question context: "
                << quetion_context_ << std::endl;
    std::cout   << "A: " << question_choices_[0] << " "
                << "B: " << question_choices_[1] << " "
                << "C: " << question_choices_[2] << " "
                << "D: " << question_choices_[3] << " "
                << std::endl;
    std::cout   << "The correct answer is: <" << question_answer_ << ">" << std::endl;
    std::cout << std::endl;
} 
void JudgementQuestion::ShowQuestionDetail() {
    std::cout   << question_id_ << "\t"
                << course_ << "\t"
                << QuestionTypeStr[type_] << "\t"
                << mark_ 
                << std::endl;
    std::cout   << "Question context: "
                << quetion_context_ << std::endl;
    std::cout   << "True or False?" << std::endl;
    std::cout   << "The correct answer is: " << question_answer_ << std::endl;
    std::cout << std::endl;
} 
void SubjectiveQuestion::ShowQuestionDetail() {
    std::cout   << question_id_ << "\t"
                << course_ << "\t"
                << QuestionTypeStr[type_] << "\t"
                << mark_ 
                << std::endl;
    std::cout   << "Question context: "
                << quetion_context_ << std::endl;
    std::cout   << "The correct answer is: " << question_answer_ << std::endl;
    std::cout << std::endl;
} 


void ChoiceQuestion::ShowQuestionOnly() {
    std::cout   << question_id_ << "\t"
                << course_ << "\t"
                << QuestionTypeStr[type_] << "\t"
                << mark_ 
                << std::endl;
    std::cout   << "Question context: "
                << quetion_context_ << std::endl;
    std::cout   << "A: " << question_choices_[0] << " "
                << "B: " << question_choices_[1] << " "
                << "C: " << question_choices_[2] << " "
                << "D: " << question_choices_[3] << " "
                << std::endl;
    std::cout << std::endl;
}
void JudgementQuestion::ShowQuestionOnly() {
    std::cout   << question_id_ << "\t"
                << course_ << "\t"
                << QuestionTypeStr[type_] << "\t"
                << mark_ 
                << std::endl;
    std::cout   << "Question context: "
                << quetion_context_ << std::endl;
    std::cout   << "True or False?" << std::endl;
    std::cout << std::endl;
}
void SubjectiveQuestion::ShowQuestionOnly() {
    std::cout   << question_id_ << "\t"
                << course_ << "\t"
                << QuestionTypeStr[type_] << "\t"
                << mark_ 
                << std::endl;
    std::cout   << "Question context: "
                << quetion_context_ << std::endl;
    std::cout << std::endl;
}

