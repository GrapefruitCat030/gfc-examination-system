#pragma once

#include<vector>
#include<string>

struct UserRecord {
    int user_id_;
    std::string user_name_;
    std::string password_;
    int authority_;
};

#include"schedule.h"
#include"question.h"
#include"paper.h"
#include"answer.h"


// #include "database_repository.h"

// 数据库服务类使用Repository模式
class DataBaseService {
public:
    /* TODO: temporarily use csv format. */
    
    std::vector<UserRecord> GetAllUserRecord();    
    UserRecord GetUserRecordByName(std::string username);
    void AddUser(UserRecord &, bool is_teacher);
    void DeleteUser(int user_id);

    std::vector<Schedule> GetAllSchedule();
    Schedule GetScheduleById(int schedule_id);
    void UpdateSchedule(Schedule &);
    void AddSchedule(Schedule &);
    void DeleteSchedule(int schedule_id);

    std::vector<Question> GetAllQusetion();
    Question GetQuestionById(int question_id);
    void AddQuestion(Question &);
    void DeleteQuestion(int question_id);

    std::vector<Paper> GetAllPaper();
    Paper GetPaperById(int paper_id);
    void AddPaper(Paper &);
    void DeletePaper(int paper_id);

    std::vector<Answer> GetAllAnswer();
    Answer GetAnswerById(int answer_id);
    void AddAnswer(Answer &);
    void DeleteAnswer(int answer_id);
    void UpdateAnswer(Answer &);


// private:
//     std::unique_ptr<IDataBaseRepository> userRepository;

// public:
//     void SetUserRepository(std::unique_ptr<IDataBaseRepository> repository) {
//         userRepository = std::move(repository);
//     }

//     void Connect() {
//         // 连接数据库的逻辑
//     }

//     void Disconnect() {
//         // 断开数据库连接的逻辑
//     }

//     void CreateItem() {
//         userRepository->CreateItem();
//     }

//     void FindItem() {
//         userRepository->FindItem();
//     }

//     void UpdateItem() {
//         userRepository->UpdateItem();
//     }

//     void DeleteItem() {
//         userRepository->DeleteItem();
//     }
};