#include"questionbank_service.h"

#include<iostream>

QuestionBankService::QuestionBankService(DataBaseService *dbs, LogService *lgs) : db_service_(dbs), log_service_(lgs) {
   question_list = db_service_->ReadQuestionCSV();
   cq_list = db_service_->ReadChoiceQuestionCSV();
   jq_list = db_service_->ReadJudgementQuestionCSV();
   sq_list = db_service_->ReadSubjectiveQuestionCSV();
}

void       QuestionBankService::ViewQuestionList() { 
   std::cout << "Attention: Question detail see in <Choose Question>.\n\n";

   // question_list = db_service_->ReadQuestionCSV();
   for(auto& q: question_list) {
      q.ShowQuestionDetail();
   }
   std::cout << std::endl;
}
void       QuestionBankService::AddQuestion() { 
   Question tmp;

   tmp.mark_ = 0;
   std::cout << "Enter question id: ";
   std::cin >> tmp.question_id_;
   std::cout << "Enter course name: ";
   std::cin >> tmp.course_;
   std::cout << "Choose Question Type:\n"
               "1.Choice 2.Judgement 3.Subject\n"
               ">>> ";
   std::string input;
   std::cin >> input;  // 获取并返回第一个字符
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 清除输入缓冲区
   int rc = (input[0]) - '0';
   std::cout << "Enter question context(NO COLUMN): ";
   std::getline(std::cin, tmp.quetion_context_);
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 清除输入缓冲区

   if(rc == 1) {
      tmp.type_ = kQuestionTypeChoice;
      question_list.push_back(tmp);
      ChoiceQuestion tmpcq(tmp);
      for(int i = 0; i < 4; i++) {
         std::printf("Enter the %d choice context:\n" 
                     ">>> ",
                     i+1);
         std::getline(std::cin, tmpcq.question_choices_[i]);
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 清除输入缓冲区
      }
      while(true) {
         std::cout << "Select the correct answer:(1,2,3,4)\n"
                      ">>> ";
         int k; std::cin >> k;
         if(k == 1 || k == 2 || k == 3 || k == 4) {
            tmpcq.question_answer_ = k;
            break;
         }
         else {
            std::cout << "Error choice, try again.\n";
            continue;
         }
      }
      cq_list.push_back(tmpcq);

      db_service_->WriteQuestionCSV(question_list);
      db_service_->WriteChoiceQuestionCSV(cq_list);
   
   }
   else if(rc == 2) {
      tmp.type_ = kQuestionTypeJudge;
      question_list.push_back(tmp);
      JudgementQuestion tmpjq(tmp);
      while(true) {
         std::cout << "Select the correct answer:(1,0)\n"
                      ">>> ";
         int k; std::cin >> k;
         if(k == 1 || k == 0 ) {
            tmpjq.question_answer_ = (bool)k;
            break;
         }
         else {
            std::cout << "Error choice, try again.\n";
            continue;
         }
      }
      jq_list.push_back(tmpjq);

      db_service_->WriteQuestionCSV(question_list);
      db_service_->WriteJudgementQuestionCSV(jq_list);
   }
   else if(rc == 3) {
      tmp.type_ = kQuestionTypeSubject;
      question_list.push_back(tmp);
      SubjectiveQuestion tmpsq(tmp);
      std::cout << "Input the question answer:\n"
                   ">>> ";
      std::string input;
      std::getline(std::cin, input);
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 清除输入缓冲区
      tmpsq.question_answer_ = input;

      sq_list.push_back(tmpsq);

      db_service_->WriteQuestionCSV(question_list);
      db_service_->WriteSubjectiveQuestionCSV(sq_list);
   }
}
void       QuestionBankService::ChooseQuestion() { 
   int id;
   std::cout << "Enter the question id: ";
   std::cin >> id;
   std::cout << std::endl;
   
   // question_list = db_service_->ReadQuestionCSV();
   for(const auto& q: question_list) {
      if(q.question_id_ != id) continue;
      
      if(q.type_ == kQuestionTypeChoice) {
         for(auto& cq: cq_list) {
            if(cq.question_id_ != q.question_id_) continue;
            cq.ShowQuestionDetail();      
           
            return;
         } 
      }
      else if(q.type_ == kQuestionTypeJudge) {
         for(auto& jq: jq_list) {
            if(jq.question_id_ != q.question_id_) continue;
            jq.ShowQuestionDetail();      
            return;
         } 
      }
      else if(q.type_ == kQuestionTypeSubject) {
         for(auto& sq: sq_list) {
            if(sq.question_id_ != q.question_id_) continue;
            sq.ShowQuestionDetail();
            return;
         }
      }
      else abort();
   }
   std::cout << "Cannot Found the Question.\n";
   return;
}
