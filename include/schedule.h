#pragma once

class Schedule {
    int         schedule_id_;
    std::string schedule_date_;
    std::string time_begin_;
    std::string time_end_;
    CourseType  course_;
    int         paper_id_;
    bool        request_flag_;
    
    void set_request_flag(bool);
};