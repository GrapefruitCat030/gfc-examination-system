#pragma once

#include<vector>
#include<string>

struct UserRecord {
    int user_id_;
    std::string user_name_;
    std::string password_;
    int authority_;
};


// #include "database_repository.h"

// 数据库服务类使用Repository模式
class DataBaseService {
public:
    /* TODO: temporarily use csv format. */
    
    std::vector<UserRecord> GetAllUserRecord();    
    UserRecord GetUserRecordByName(std::string username);
    void AddUser(UserRecord &, bool is_teacher);
    void DeleteUser(int user_id);


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