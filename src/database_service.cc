#include"database_service.h"
#include<iostream>
#include<fstream>
#include<sstream>

const char *user_csv = "database/user.csv";
const char *schedule_csv = "database/schedule.csv";

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
        file<< record.user_id_ << ","
            << record.user_name_ << ","
            << record.password_ << ","
            << record.authority_ << "\n";
        std::cout << "用户添加成功！\n";
    } else {
        std::cout << "无法打开文件！\n";
    }
}
void DataBaseService::DeleteUser(std::string user_id) {
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
                    if (userId != user_id) {
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


std::vector<Schedule> DataBaseService::ReadScheduleCSV() {
    std::vector<Schedule> records;
    std::ifstream file(schedule_csv);
    if (file) {
            std::string line;
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string sid, begin_time, end_time, course, pid, flag;
                std::getline(ss, sid, ',');
                std::getline(ss, begin_time, ',');
                std::getline(ss, end_time, ',');
                std::getline(ss, course, ',');
                std::getline(ss, pid, ',');
                std::getline(ss, flag, ',');
                records.push_back({std::stoi(sid), begin_time, end_time, course, std::stoi(pid), (bool)(std::stoi(flag))});
            }
    } else {
        perror("open schedule csv.");
        exit(-1);
    }
    return records;
}
void DataBaseService::WriteScheduleCSV(std::vector<Schedule> &records) {
    std::ofstream file(schedule_csv);
    if (file) {
        for (const auto& record : records) {
            file<< record.schedule_id_ << ","
                << record.time_begin_<< ","
                << record.time_end_<< ","
                << record.course_<< ","
                << record.paper_id_<< ","
                << record.request_flag_
                << std::endl;
        }
        file.close();
    }
} 

