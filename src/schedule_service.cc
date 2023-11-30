#include "schedule_service.h"

#include"schedule.h"
#include<iostream>
#include<ctime>

ScheduleService::ScheduleService(DataBaseService *dbs, LogService *lgs) : db_service_(dbs), log_service_(lgs){
    schedule_list_ = db_service_->ReadScheduleCSV();
} 


void ScheduleService::ViewSchedule() {
    schedule_list_ = db_service_->ReadScheduleCSV();
    for(auto record: schedule_list_) {
        if(record.request_flag_ == true) {
            std::cout   << record.schedule_id_ << "\t"\
                        << record.time_begin_<< "\t"\
                        << record.time_end_<< "\t"\
                        << record.course_<< "\t"\
                        << record.paper_id_<< "\t"\
                        << std::endl;
        }
    }
    std::cout << std::endl;
}
// Admin Interface
void ScheduleService::CheckScheduleRequest() { 
    for(auto record: schedule_list_) {
        if(record.request_flag_ == false) {
            std::cout   << record.schedule_id_ << "\t"\
                        << record.time_begin_<< "\t"\
                        << record.time_end_<< "\t"\
                        << record.course_<< "\t"\
                        << record.paper_id_<< "\t"\
                        << std::endl;
        }
    }
    std::cout << std::endl;
}
void ScheduleService::ChooseAndSetRequest() { 
    std::cout << "Enter target schedule id:";
    int id;
    std::cin >> id;
    for(auto &record: schedule_list_) {
        if(record.schedule_id_ == id) {
            if(record.request_flag_ == true) {
                std::cout << "It has been in schedule list.\n";
                return;
            }
            std::cout << std::endl 
                << record.schedule_id_ << "\t"\
                << record.time_begin_<< "\t"\
                << record.time_end_<< "\t"\
                << record.course_<< "\t"\
                << record.paper_id_<< "\t"\
                << std::endl;
            std::cout << "Pass it sure?\n"
                        << "1.Yes 2.No\n"
                        << ">>> ";
            std::string input;
            std::cin >> input;  // 获取并返回第一个字符
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 清除输入缓冲区
            std::cout << std::endl;

            /* Choose Service */
            int rc = (input[0]) - '0';
            if(rc == 1) {
                record.request_flag_ = true;
                db_service_->WriteScheduleCSV(schedule_list_);
                std::cout << "Modify success.\n";
            }
            else if(rc == 2) {
                return;
            }
            else abort();
        }
    }
}
void ScheduleService::AddSchedule() { 
    Schedule tmp;

    tmp.request_flag_ = true;
    std::cout << "Enter id: ";
    std::cin >> tmp.schedule_id_;
    std::cout << "Enter begin time: ";
    std::cin >> tmp.time_begin_;
    std::cout << "Enter end time: ";
    std::cin >> tmp.time_end_;
    std::cout << "Enter course: ";
    std::cin >> tmp.course_;
    std::cout << "Enter pid: ";
    std::cin >> tmp.paper_id_;

    schedule_list_.push_back(tmp);

    db_service_->WriteScheduleCSV(schedule_list_);
}
// Teacher Interface
void ScheduleService::CommitScheduleRequest() { 
    Schedule tmp;

    tmp.request_flag_ = false;
    std::cout << "Enter id: ";
    std::cin >> tmp.schedule_id_;
    std::cout << "Enter begin time: ";
    std::cin >> tmp.time_begin_;
    std::cout << "Enter end time: ";
    std::cin >> tmp.time_end_;
    std::cout << "Enter course: ";
    std::cin >> tmp.course_;
    std::cout << "Enter pid: ";
    std::cin >> tmp.paper_id_;

    schedule_list_.push_back(tmp);

    db_service_->WriteScheduleCSV(schedule_list_);
}
// Student Interface
void ScheduleService::RemindSchedule() { 
    std::cout << "\nThe Deadline Exam Day is Here !!!\n" << std::endl;

    // 获取当前系统时间
    std::time_t currentTime = std::time(nullptr);
    std::tm *current = std::localtime(&currentTime);

    for(auto record: schedule_list_) {
        if(record.request_flag_ == true) {
            std::string recordtime = record.time_begin_;
            // 解析时间戳字符串
            std::tm timeinfo = {};
            if (std::sscanf(recordtime.c_str(), "%d-%d-%d-%d-%d",
                            &timeinfo.tm_year, &timeinfo.tm_mon, &timeinfo.tm_mday,
                            &timeinfo.tm_hour, &timeinfo.tm_min) != 5) {
                std::cerr << "Failed to parse timestamp: " << recordtime << std::endl;
                continue;
            }
            timeinfo.tm_year -= 1900;  // 年份需要减去1900
            timeinfo.tm_mon -= 1;      // 月份需要减去1
        
            // 计算时间差（单位为秒）
            std::time_t timestamp = std::mktime(&timeinfo);
            std::time_t currentTimestamp = std::mktime(current);
            const int secondsPerDay = 24 * 60 * 60;
            int diff = std::difftime(timestamp, currentTimestamp);

            // 判断时间差是否小于3天
            if (diff > 0 && diff <= 3 * secondsPerDay) {
                std::cout   << record.schedule_id_ << "\t"\
                        << record.time_begin_<< "\t"\
                        << record.time_end_<< "\t"\
                        << record.course_<< "\t"\
                        << record.paper_id_<< "\t"\
                        << std::endl;
            }
        }
    }
    std::cout << std::endl;
}


