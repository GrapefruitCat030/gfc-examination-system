#pragma once 

#include"constant.h"
#include<string>
#include<vector>

class Paper {
    int         paper_id_;
    CourseType  course_;    
    std::string paper_name_;
    int         total_mark_;
    std::vector<int> question_id_list_;
    void ShowPaper();
};