#include"paperbank_service.h"
#include<iostream>


PaperBankService::PaperBankService(DataBaseService *dbs, LogService *lgs) : db_service_(dbs), log_service_(lgs){
    paper_list = db_service_->ReadPaperCSV();
}
PaperBankService::~PaperBankService() {

}

void       PaperBankService::ViewPaperList() {
   std::cout << "Attention: Paper detail see in <View One>.\n\n";
   for(auto& p: paper_list) {
        p.ShowPaper(); 
   }
   std::cout << std::endl;
}
void       PaperBankService::ViewPaper() {
    
    std::vector<Question> question_list = db_service_->ReadQuestionCSV();
    std::vector<ChoiceQuestion> cq_list = db_service_->ReadChoiceQuestionCSV();
    std::vector<JudgementQuestion> jq_list = db_service_->ReadJudgementQuestionCSV();
    std::vector<SubjectiveQuestion> sq_list = db_service_->ReadSubjectiveQuestionCSV();
   
    std::cout << "Enter the paper ID: ";
    int id;
    std::cin >> id;
    for(auto& p:paper_list) {
        if(p.paper_id_ == id) {
            std::cout << std::endl;
            p.ShowPaper();
            std::cout << std::endl;

            for(auto& qid:p.question_id_list_) {
                for(const auto& q: question_list) {
                    if(q.question_id_ != qid) continue;
                    
                    if(q.type_ == kQuestionTypeChoice) {
                        for(auto& cq: cq_list) {
                            if(cq.question_id_ != q.question_id_) continue;
                            cq.ShowQuestionOnly();      
                            break;
                        } 
                    }
                    else if(q.type_ == kQuestionTypeJudge) {
                        for(auto& jq: jq_list) {
                            if(jq.question_id_ != q.question_id_) continue;
                            jq.ShowQuestionOnly();      
                            break;
                        } 
                    }
                    else if(q.type_ == kQuestionTypeSubject) {
                        for(auto& sq: sq_list) {
                            if(sq.question_id_ != q.question_id_) continue;
                            sq.ShowQuestionOnly();
                            break;
                        }
                    }
                    else abort();
                }
            }
            return;
        }
    }
}

void       PaperBankService::AddPaper() {
    Paper tmp;

    std::cout << "Enter paper id: ";
    std::cin >> tmp.paper_id_;
    std::cout << "Enter course name: ";
    std::cin >> tmp.course_;
    std::cout << "Enter paper name: ";
    std::cin >> tmp.paper_name_;
    std::cout << "Enter total mark: ";
    std::cin >> tmp.total_mark_;

    while(true) {
        int qid;
        std::cout << "Enter Question ID: ";
        std::cin >> qid;
        tmp.question_id_list_.push_back(qid);

        std::cout << "Continue? 1 or 0 exit.\n"
                    << ">>> ";
        std::string input;
        std::cin >> input;  // 获取并返回第一个字符
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 清除输入缓冲区
        int rc = (input[0]) - '0';
        if(rc == 0) break;
    } 

    paper_list.push_back(tmp);
    db_service_->WritePaperCSV(paper_list);
}