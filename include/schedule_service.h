#pragma once

#include<vector>

#include "schedule.h"
#include "database_service.h"
#include "log_service.h"

// Admin Interface
class IScheduleServiceAdmin {
public:
    virtual ~IScheduleServiceAdmin() {};
    virtual void CheckScheduleRequest() = 0;
    virtual void ChooseAndSetRequest() = 0;
    virtual void AddSchedule() = 0;
    virtual void ViewSchedule() = 0;
}; 
// Teacher Interface
class IScheduleServiceTeacher {
public:
    virtual ~IScheduleServiceTeacher() {};
    virtual void CommitScheduleRequest() = 0;
    virtual void ViewSchedule() = 0;
}; 
// Student Interface
class IScheduleServiceStudent {
public:
    virtual ~IScheduleServiceStudent() {};
    virtual void RemindSchedule() = 0;
    virtual void ViewSchedule() = 0;
}; 
// 查看考试安排，主动添加考试安排，教师提交考试安排请求，审议考试安排请求
class ScheduleService : public IScheduleServiceAdmin, public IScheduleServiceTeacher, public IScheduleServiceStudent {	
public:
    DataBaseService *db_service_; 
    LogService      *log_service_;
    std::vector<Schedule> schedule_list_;

    ScheduleService(DataBaseService *, LogService *);
    ~ScheduleService() {};
    void ViewSchedule() override;
    // Admin Interface
    void CheckScheduleRequest() override;
    void ChooseAndSetRequest() override;
    void AddSchedule() override;
    // Teacher Interface
    void CommitScheduleRequest() override;
    // Student Interface
    void RemindSchedule() override;
};
