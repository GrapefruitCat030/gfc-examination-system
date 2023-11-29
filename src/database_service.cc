#include"database_service.h"
#include<iostream>
#include<fstream>
#include<sstream>

const char *user_csv = "database/user.csv";

std::vector<UserRecord> DataBaseService::GetAllUserRecord() {
    std::vector<UserRecord> records;
    std::ifstream file(user_csv);
    if (file) {
            std::string line;
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string userId, userName, password, authority;
                std::getline(ss, userId, ',');
                std::getline(ss, userName, ',');
                std::getline(ss, password, ',');
                std::getline(ss, authority, ',');
                records.push_back({std::stoi(userId), userName, password, std::stoi(authority)});
            }
    } else {
        std::cout << "无法打开文件！\n";
        exit(-1);
    }
    return records;
}    
UserRecord DataBaseService::GetUserRecordByName(std::string username) {
     std::ifstream inputFile(user_csv);
        if (inputFile) {
            std::string line;
            while (std::getline(inputFile, line)) {
                std::stringstream ss(line);
                std::string userId, userNameFromRecord, password, authority;
                std::getline(ss, userId, ',');
                std::getline(ss, userNameFromRecord, ',');
                std::getline(ss, password, ',');
                std::getline(ss, authority, ',');
                if (username == userNameFromRecord) {
                    return {std::stoi(userId), userNameFromRecord, password, std::stoi(authority)};
                }
            }
        } else {
            std::cout << "无法打开文件！\n";
        }
        return UserRecord{};
}
void DataBaseService::AddUser(UserRecord &record, bool is_teacher) {
    std::ofstream file(user_csv, std::ios::app);
    if (file) {
        file << std::endl  
            << record.user_id_ << ","
            << record.user_name_ << ","
            << record.password_ << ","
            << record.authority_ << "\n";
        std::cout << "用户添加成功！\n";
    } else {
        std::cout << "无法打开文件！\n";
    }
}
void DataBaseService::DeleteUser(int user_id) {
     std::ifstream inputFile(user_csv);
        if (inputFile) {
            std::ofstream outputFile("temp.csv");
            if (outputFile) {
                std::string line;
                while (std::getline(inputFile, line)) {
                    std::stringstream ss(line);
                    std::string userId, userNameFromRecord, password, authority;
                    std::getline(ss, userId, ',');
                    std::getline(ss, userNameFromRecord, ',');
                    std::getline(ss, password, ',');
                    std::getline(ss, authority, ',');
                    if (std::stoi(userId) != user_id) {
                        outputFile << line << "\n";
                    }
                }
                inputFile.close();
                outputFile.close();
                std::remove(user_csv);
                std::rename("temp.csv", user_csv);
                std::cout << "记录删除成功！\n";
            } else {
                std::cout << "无法创建临时文件！\n";
            }
        } else {
            std::cout << "无法打开文件！\n";
        }
}