#pragma once

#include<string>

struct Schedule {
    int         schedule_id_;
    std::string time_begin_;
    std::string time_end_;
    std::string course_;
    int         paper_id_;
    bool        request_flag_;
};