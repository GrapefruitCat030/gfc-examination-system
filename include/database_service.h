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
    void DeleteUser(std::string user_id);

    std::vector<Schedule> ReadScheduleCSV();
    void WriteScheduleCSV(std::vector<Schedule> &); 
    // Schedule GetScheduleById(std::string schedule_id);
    // void UpdateSchedule(Schedule &);
    // void AddSchedule(Schedule &);
    // void DeleteSchedule(std::string schedule_id);

    std::vector<Question> ReadQuestionCSV();
    void WriteQuestionCSV(std::vector<Question> &);
    // Question GetQuestionById(std::string question_id);
    // void AddQuestion(Question &);
    // void DeleteQuestion(std::string question_id);
    std::vector<ChoiceQuestion> ReadChoiceQuestionCSV();
    void WriteChoiceQuestionCSV(std::vector<ChoiceQuestion> &);    
    
    std::vector<JudgementQuestion> ReadJudgementQuestionCSV();
    void WriteJudgementQuestionCSV(std::vector<JudgementQuestion> &);    
    
    std::vector<SubjectiveQuestion> ReadSubjectiveQuestionCSV();
    void WriteSubjectiveQuestionCSV(std::vector<SubjectiveQuestion> &);



    std::vector<Paper> ReadPaperCSV();
    void WritePaperCSV(std::vector<Paper> &);
    // Paper GetPaperById(std::string paper_id);
    // void AddPaper(Paper &);
    // void DeletePaper(std::string paper_id);

    
    std::vector<Answer> ReadAnswerCSV();
    void WriteAnswerSheetCSV(std::vector<Answer> &);

    std::vector<AnswerSheet> ReadAnswerSheetCSV();
    void WriteAnswerSheetCSV(std::vector<AnswerSheet> &);
    // Answer GetAnswerById(std::string answer_id);
    // void AddAnswer(Answer &);
    // void DeleteAnswer(std::string answer_id);
    // void UpdateAnswer(Answer &);

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