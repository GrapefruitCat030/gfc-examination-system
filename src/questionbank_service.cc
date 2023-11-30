#include"questionbank_service.h"

#include<iostream>

QuestionBankService::QuestionBankService(DataBaseService *dbs, LogService *lgs) : db_service_(dbs), log_service_(lgs) {
   question_list = db_service_->ReadQuestionCSV();
   cq_list = db_service_->ReadChoiceQuestionCSV();
   jq_list = db_service_->ReadJudgementQuestionCSV();
   sq_list = db_service_->ReadSubjectiveQuestionCSV();
}


void       QuestionBankService::ViewQuestionList() { 
   question_list = db_service_->ReadQuestionCSV();
   for(auto& q: question_list) {
      q.ShowQuestion();
   }
   std::cout << std::endl;
}
Question   QuestionBankService::CreateQuestion() { 
   return Question{}; 
}
void       QuestionBankService::AddQuestion() { 
    
}
void       QuestionBankService::ChooseQuestion() { 
   int id;
   std::cout << "Enter the question id: ";
   std::cin >> id;

   question_list = db_service_->ReadQuestionCSV();
   for(const auto& q: question_list) {
      if(q.question_id_ != id) continue;
      
      if(q.type_ == kQuestionTypeChoice) {
         for(auto& cq: cq_list) {
            if(cq.question_id_ != q.question_id_) continue;
            cq.ShowQuestion();      
            return;
         } 
      }
      else if(q.type_ == kQuestionTypeJudge) {
         for(auto& jq: jq_list) {
            if(jq.question_id_ != q.question_id_) continue;
            jq.ShowQuestion();      
            return;
         } 
      }
      else if(q.type_ == kQuestionTypeSubject) {
         for(auto& sq: sq_list) {
            if(sq.question_id_ != q.question_id_) continue;
            sq.ShowQuestion();
            return;
         }
      }
      else abort();
   }
   std::cout << "Cannot Found the Question.\n";
   return;
}
