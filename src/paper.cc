#include"paper.h"
#include<iostream>

void Paper::ShowPaper() {
    std::cout   << paper_id_ << "\t"
                << course_ << "\t"
                << paper_name_ << "\t"
                << total_mark_ 
                << std::endl;
}
