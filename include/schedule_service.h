#pragma once

#include<vector>

#include "schedule.h"
#include "database_service.h"
#include "log_service.h"

// Admin Interface
class IScheduleServiceAdmin {
public:
    virtual void CheckScheduleRequest();
    virtual void ChooseAndSetRequest();
    virtual void AddSchedule();
    virtual void ViewSchedule();
}; 
// Teacher Interface
class IScheduleServiceTeacher {
public:
    virtual void CommitScheduleRequest();
    virtual void ViewSchedule();
}; 
// Student Interface
class IScheduleServiceStudent {
public:
    virtual void RemindSchedule();
    virtual void ViewSchedule();
}; 
// 查看考试安排，主动添加考试安排，教师提交考试安排请求，审议考试安排请求
class ScheduleService : public IScheduleServiceAdmin, public IScheduleServiceTeacher, public IScheduleServiceStudent {	
public:
    DataBaseService *db_service_; 
    LogService      *log_service_;
    std::vector<Schedule> schedule_list_;

    ScheduleService(DataBaseService *, LogService *);
    void ViewSchedule();
    // Admin Interface
    void CheckScheduleRequest() override;
    void ChooseAndSetRequest() override;
    void AddSchedule() override;
    // Teacher Interface
    void CommitScheduleRequest() override;
    // Student Interface
    void RemindSchedule() override;
};
