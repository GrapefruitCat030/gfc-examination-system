#pragma once 

#include<variant>
#include<string>
#include<vector>

struct Answer {
    int answer_id_;
    int question_id_;
    std::variant<int, bool, std::string> answer_context_;
    std::string answer_context_;
    int mark_;
};
class AnswerSheet {
    int answer_sheet_id_;
    int paper_id_;
    int student_id_;
    int total_mark_;
    std::vector<Answer> answer_list_;
    
    void ShowAnswerSheet();
};