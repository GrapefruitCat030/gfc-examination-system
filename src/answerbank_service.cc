#include "answerbank_service.h"
#include<iostream>


AnswerBankService::AnswerBankService(DataBaseService *dbs, LogService *lgs) : db_service_(dbs), log_service_(lgs) {
    answer_list_ = db_service_->ReadAnswerCSV();
    answer_sheet_list_ = db_service_->ReadAnswerSheetCSV();
}

// Teacher Interface
void AnswerBankService::ViewAnswerList() {
    answer_list_ = db_service_->ReadAnswerCSV();
    answer_sheet_list_ = db_service_->ReadAnswerSheetCSV();
    for(auto record: answer_sheet_list_) {
        std::cout   << record.answer_sheet_id_ << "\t"\
                    << record.paper_id_ << "\t"\
                    << record.student_id_ << "\t"\
                    << record.total_mark_
                    << std::endl;
    }
    std::cout << std::endl;
};
void AnswerBankService::CorrectAnswer() {
    std::vector<Question> question_list = db_service_->ReadQuestionCSV();
    std::vector<ChoiceQuestion> cq_list = db_service_->ReadChoiceQuestionCSV();
    std::vector<JudgementQuestion> jq_list = db_service_->ReadJudgementQuestionCSV();
    std::vector<SubjectiveQuestion> sq_list = db_service_->ReadSubjectiveQuestionCSV();

    std::cout << "Enter the answer sheet ID:";
    int id; std::cin >> id;
    for(auto& as: answer_sheet_list_) {
        if(as.answer_sheet_id_ == id) {
            as.total_mark_ = 0;
            for(auto& a: as.answer_list_) {
                for(auto& q: question_list) {
                    if(q.question_id_ == a.question_id_) {
                        if(q.type_ == kQuestionTypeChoice) {
                            for(auto& cq: cq_list) {
                                if(cq.question_id_ != q.question_id_) continue;
                                cq.ShowQuestionOnly();      
                                std::cout << "The student answer is: " << std::get<int>(a.answer_context_) << std::endl;
                            } 
                        }
                        else if(q.type_ == kQuestionTypeJudge) {
                            for(auto& jq: jq_list) {
                                if(jq.question_id_ != q.question_id_) continue;
                                jq.ShowQuestionOnly();      
                                std::cout << "The student answer is: " << std::get<bool>(a.answer_context_) << std::endl;
                            } 
                        }
                        else if(q.type_ == kQuestionTypeSubject) {
                            for(auto& sq: sq_list) {
                                if(sq.question_id_ != q.question_id_) continue;
                                sq.ShowQuestionOnly();
                                std::cout << "The student answer is: " << std::get<std::string>(a.answer_context_) << std::endl;
                            }
                        }
                        break;
                    }
                }
                std::cout << "Give it mark: ";
                int m; std::cin >> m;
                a.mark_ = m;
                for(auto& ta: answer_list_) {
                    if(ta.answer_sheet_id_ == as.answer_sheet_id_ && ta.question_id_ == a.question_id_){
                        ta.mark_ = m;
                    }
                }
                as.total_mark_ += m;
            } 
            break;
        }
    } 
    db_service_->WriteAnswerCSV(answer_list_);
    db_service_->WriteAnswerSheetCSV(answer_sheet_list_);
};
// Student Interface
void AnswerBankService::StartAnswer() {
    

    AnswerSheet tmpas;
    tmpas.answer_sheet_id_ = answer_sheet_list_.back().answer_sheet_id_ + 1;

    std::cout << "Enter Your Student ID: ";
    int uid; std::cin >> uid;
    std::cout << "Choose your exam paper id: ";
    int pid; std::cin >> pid;
    tmpas.student_id_ = uid;
    tmpas.paper_id_ = pid;
    tmpas.total_mark_ = 0;

    std::vector<Paper> paper_list = db_service_->ReadPaperCSV();
    std::vector<Question> question_list = db_service_->ReadQuestionCSV();
    std::vector<ChoiceQuestion> cq_list = db_service_->ReadChoiceQuestionCSV();
    std::vector<JudgementQuestion> jq_list = db_service_->ReadJudgementQuestionCSV();
    std::vector<SubjectiveQuestion> sq_list = db_service_->ReadSubjectiveQuestionCSV();
   
    for(auto& p:paper_list) {
        if(p.paper_id_ == pid) {
            std::cout << std::endl;
            p.ShowPaper();
            std::cout << std::endl;

            for(auto& qid:p.question_id_list_) {
                for(const auto& q: question_list) {
                    if(q.question_id_ != qid) continue;

                    Answer a;
                    a.answer_sheet_id_ = tmpas.answer_sheet_id_;
                    a.question_id_ = qid;
                    a.mark_ = 0;
                    if(q.type_ == kQuestionTypeChoice) {
                        for(auto& cq: cq_list) {
                            if(cq.question_id_ != q.question_id_) continue;
                            cq.ShowQuestionOnly();      
                            std::cout << "Enter your answer(1,2,3,4): ";
                            int c; std::cin >> c;
                            a.answer_context_ = c;
                            break;
                        } 
                    }
                    else if(q.type_ == kQuestionTypeJudge) {
                        for(auto& jq: jq_list) {
                            if(jq.question_id_ != q.question_id_) continue;
                            jq.ShowQuestionOnly();      
                            std::cout << "Enter your answer(1,0): ";
                            int c; std::cin >> c;
                            a.answer_context_ = (bool)c;
                            break;
                        } 
                    }
                    else if(q.type_ == kQuestionTypeSubject) {
                        for(auto& sq: sq_list) {
                            if(sq.question_id_ != q.question_id_) continue;
                            sq.ShowQuestionOnly();
                            std::cout << "Enter your answer: ";
                            std::string c;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::getline(std::cin, c);
                            a.answer_context_ = c;
                            break;
                        }
                    }
                    else abort();
                    this->answer_list_.push_back(a);
                    tmpas.answer_list_.push_back(a);
                }
            }
        }
    }
    this->answer_sheet_list_.push_back(tmpas);

    db_service_->WriteAnswerCSV(this->answer_list_);
    db_service_->WriteAnswerSheetCSV(this->answer_sheet_list_);
};
void AnswerBankService::ViewResult() {
    std::cout << "Enter Your Student ID: ";
    int id; std::cin >> id;

    for(const auto& as:answer_sheet_list_) {
        if(as.student_id_ == id) {
            std::cout   << as.answer_sheet_id_ << "\t"\
                        << as.paper_id_ << "\t"\
                        << as.total_mark_
                        << std::endl;
        }        
    }
    std::cout << "\nEnter the Answer Sheet ID: ";
    int asid; std::cin >> asid;
    
    std::vector<Question> question_list = db_service_->ReadQuestionCSV();
    std::vector<ChoiceQuestion> cq_list = db_service_->ReadChoiceQuestionCSV();
    std::vector<JudgementQuestion> jq_list = db_service_->ReadJudgementQuestionCSV();
    std::vector<SubjectiveQuestion> sq_list = db_service_->ReadSubjectiveQuestionCSV();

    for(auto& as: answer_sheet_list_) {
        if(as.answer_sheet_id_ == asid) {
            as.total_mark_ = 0;
            for(auto& a: as.answer_list_) {
                for(auto& q: question_list) {
                    if(q.question_id_ == a.question_id_) {
                        if(q.type_ == kQuestionTypeChoice) {
                            for(auto& cq: cq_list) {
                                if(cq.question_id_ != q.question_id_) continue;
                                cq.ShowQuestionOnly();      
                                std::cout << "Your answer is: " << std::get<int>(a.answer_context_) << std::endl;
                            } 
                        }
                        else if(q.type_ == kQuestionTypeJudge) {
                            for(auto& jq: jq_list) {
                                if(jq.question_id_ != q.question_id_) continue;
                                jq.ShowQuestionOnly();      
                                std::cout << "Your answer is: " << std::get<bool>(a.answer_context_) << std::endl;
                            } 
                        }
                        else if(q.type_ == kQuestionTypeSubject) {
                            for(auto& sq: sq_list) {
                                if(sq.question_id_ != q.question_id_) continue;
                                sq.ShowQuestionOnly();
                                std::cout << "Your answer is: " << std::get<std::string>(a.answer_context_) << std::endl;
                            }
                        }
                        std::cout << "Your mark: " << a.mark_ << " Base mark: " << q.mark_ << std::endl;
                        break;
                    }
                }
            } 
            break;
        }
    } 
};

