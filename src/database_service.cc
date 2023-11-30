#include"database_service.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<utility>

const char *user_csv = "database/user.csv";
const char *schedule_csv = "database/schedule.csv";
const char *question_csv = "database/question.csv";
const char *cq_csv = "database/choice_quesion.csv";
const char *jq_csv = "database/judge_question.csv";
const char *sq_csv = "database/subject_question.csv";
const char *paper_csv = "database/paper.csv";
const char *papercomponent_csv = "database/paper_component.csv";
const char *answer_csv = "database/answer.csv";
const char *answersheet_csv = "database/answer_sheet.csv";


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

std::vector<Question> DataBaseService::ReadQuestionCSV() {
    std::vector<Question> records;
    std::ifstream file1(question_csv);
    if (file1) {
            std::string line;
            while (std::getline(file1, line)) {
                std::stringstream ss(line);
                std::string qid, course, qtype, context, mark;
                std::getline(ss, qid, ',');
                std::getline(ss, course, ',');
                std::getline(ss, qtype, ',');
                std::getline(ss, context, ',');
                std::getline(ss, mark, ',');
                Question tmp; 
                tmp.question_id_ = std::stoi(qid); 
                tmp.course_ = course; 
                tmp.type_ = (QuestionType)(std::stoi(qtype)); 
                tmp.quetion_context_ = context;
                tmp.mark_ = std::stoi(mark);
                records.push_back(tmp);
            }
    } else {
        perror("open question csv.");
        exit(-1);
    }
    return records;    
}
void DataBaseService::WriteQuestionCSV(std::vector<Question> &records) {
    std::ofstream file(question_csv);
    if (file) {
        for (const auto& record : records) {
            file<< record.question_id_ << ","
                << record.course_<< ","
                << record.type_<< ","
                << record.quetion_context_<< ","
                << record.mark_
                << std::endl;
        }
        file.close();
    }
}

std::vector<ChoiceQuestion> DataBaseService::ReadChoiceQuestionCSV() {
    std::vector<Question> question_list;
    std::ifstream file(question_csv);
    if (file) {
            std::string line;
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string qid, course, qtype, context, mark;
                std::getline(ss, qid, ',');
                std::getline(ss, course, ',');
                std::getline(ss, qtype, ',');
                std::getline(ss, context, ',');
                std::getline(ss, mark, ',');
                Question tmp; 
                tmp.question_id_ = std::stoi(qid); 
                tmp.course_ = course; 
                tmp.type_ = (QuestionType)(std::stoi(qtype)); 
                tmp.quetion_context_ = context;
                tmp.mark_ = std::stoi(mark);
                question_list.push_back(tmp);
            }
    } else {
        perror("open question csv.");
        exit(-1);
    }
    
    std::vector<ChoiceQuestion> cq_list;
    std::ifstream file1(cq_csv);
    if (file1) {
            std::string line;
            while (std::getline(file1, line)) {
                std::stringstream ss(line);
                std::string qid, c1, c2, c3, c4, answer;
                std::getline(ss, qid, ',');
                std::getline(ss, c1, ',');
                std::getline(ss, c2, ',');
                std::getline(ss, c3, ',');
                std::getline(ss, c4, ',');
                std::getline(ss, answer, ',');
                
                for(auto& q:question_list) {
                    if(std::stoi(qid) == q.question_id_) {
                        ChoiceQuestion tmpcq(q);
                        tmpcq.question_choices_ = {c1, c2, c3, c4};
                        tmpcq.question_answer_ = std::stoi(answer);
                        cq_list.push_back(tmpcq);
                    }
                } 
            }
    } else {
        perror("open choice question csv.");
        exit(-1);
    }

    return cq_list;    
}
void DataBaseService::WriteChoiceQuestionCSV(std::vector<ChoiceQuestion> &records) {
    std::ofstream file(cq_csv);
    if (file) {
        for (const auto& record : records) {
            file<< record.question_id_ << ","
                << record.question_choices_[0] << ","
                << record.question_choices_[1] << ","
                << record.question_choices_[2] << ","
                << record.question_choices_[3] << ","
                << record.question_answer_
                << std::endl;
        }
        file.close();
    }
}    

std::vector<JudgementQuestion> DataBaseService::ReadJudgementQuestionCSV() {
    std::vector<Question> question_list;
    std::ifstream file(question_csv);
    if (file) {
            std::string line;
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string qid, course, qtype, context, mark;
                std::getline(ss, qid, ',');
                std::getline(ss, course, ',');
                std::getline(ss, qtype, ',');
                std::getline(ss, context, ',');
                std::getline(ss, mark, ',');
                Question tmp; 
                tmp.question_id_ = std::stoi(qid); 
                tmp.course_ = course; 
                tmp.type_ = (QuestionType)(std::stoi(qtype)); 
                tmp.quetion_context_ = context;
                tmp.mark_ = std::stoi(mark);
                question_list.push_back(tmp);
            }
    } else {
        perror("open question csv.");
        exit(-1);
    }
    
    std::vector<JudgementQuestion> jq_list;
    std::ifstream file1(jq_csv);
    if (file1) {
            std::string line;
            while (std::getline(file1, line)) {
                std::stringstream ss(line);
                std::string qid, answer;
                std::getline(ss, qid, ',');
                std::getline(ss, answer, ',');
                
                for(auto& q:question_list) {
                    if(std::stoi(qid) == q.question_id_) {
                        JudgementQuestion tmpjq(q);
                        tmpjq.question_answer_ = (bool)std::stoi(answer);
                        jq_list.push_back(tmpjq);
                    }
                } 
            }
    } else {
        perror("open judge question csv.");
        exit(-1);
    }

    return jq_list;    
}
void DataBaseService::WriteJudgementQuestionCSV(std::vector<JudgementQuestion> &records) {
    std::ofstream file(jq_csv);
    if (file) {
        for (const auto& record : records) {
            file<< record.question_id_ << ","
                << record.question_answer_
                << std::endl;
        }
        file.close();
    }
}    

std::vector<SubjectiveQuestion> DataBaseService::ReadSubjectiveQuestionCSV() {
    std::vector<Question> question_list;
    std::ifstream file(question_csv);
    if (file) {
            std::string line;
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string qid, course, qtype, context, mark;
                std::getline(ss, qid, ',');
                std::getline(ss, course, ',');
                std::getline(ss, qtype, ',');
                std::getline(ss, context, ',');
                std::getline(ss, mark, ',');
                Question tmp; 
                tmp.question_id_ = std::stoi(qid); 
                tmp.course_ = course; 
                tmp.type_ = (QuestionType)(std::stoi(qtype)); 
                tmp.quetion_context_ = context;
                tmp.mark_ = std::stoi(mark);
                question_list.push_back(tmp);
            }
    } else {
        perror("open question csv.");
        exit(-1);
    }
    
    std::vector<SubjectiveQuestion> sq_list;
    std::ifstream file1(sq_csv);
    if (file1) {
            std::string line;
            while (std::getline(file1, line)) {
                std::stringstream ss(line);
                std::string qid, answer;
                std::getline(ss, qid, ',');
                std::getline(ss, answer, ',');
                
                for(auto& q:question_list) {
                    if(std::stoi(qid) == q.question_id_) {
                        SubjectiveQuestion tmpsq(q);
                        tmpsq.question_answer_ = answer;
                        sq_list.push_back(tmpsq);
                    }
                } 
            }
    } else {
        perror("open subject question csv.");
        exit(-1);
    }

    return sq_list;    
}
void DataBaseService::WriteSubjectiveQuestionCSV(std::vector<SubjectiveQuestion> &records) {
    std::ofstream file(sq_csv);
    if (file) {
        for (const auto& record : records) {
            file<< record.question_id_ << ","
                << record.question_answer_
                << std::endl;
        }
        file.close();
    }
}


std::vector<Paper> DataBaseService::ReadPaperCSV() {
    std::vector<std::pair<int, int>> component_list;
    std::ifstream file1(papercomponent_csv);
    if(file1) {
        std::string line;
        while (std::getline(file1, line)) {
            std::stringstream ss(line);
            std::string pid, qid;
            std::getline(ss, pid, ',');
            std::getline(ss, qid, ',');
            component_list.push_back({std::stoi(pid),std::stoi(qid)});
        }
    }
    else {
        perror("open schedule csv.");
        exit(-1);
    }

    std::vector<Paper> records;
    std::ifstream file(paper_csv);
    if (file) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string pid, course, name, mark;
            std::getline(ss, pid, ',');
            std::getline(ss, course, ',');
            std::getline(ss, name, ',');
            std::getline(ss, mark, ',');
            
            Paper tmp;
            tmp.paper_id_ = std::stoi(pid);
            tmp.course_   = course;
            tmp.paper_name_ = name;
            tmp.total_mark_ = std::stoi(mark);

            for(auto& cp:component_list) {
                if(cp.first == tmp.paper_id_) {
                    tmp.question_id_list_.push_back(cp.second);
                }
            }           
            records.push_back(tmp);
        }
    } else {
        perror("open schedule csv.");
        exit(-1);
    }
    return records;
}
void DataBaseService::WritePaperCSV(std::vector<Paper> &paper_list) {
    std::ofstream file1(paper_csv), file2(papercomponent_csv);
    if (file1 && file2) {
        for (const auto& p : paper_list) {
            file1 << p.paper_id_ << ","
                << p.course_   << ","
                << p.paper_name_   << ","
                << p.total_mark_  
                << std::endl;
            for(const auto& c:p.question_id_list_) {
                file1 << p.paper_id_ << "," << c
                    << std::endl;
            } 
        }
        file1.close();
    }
}

std::vector<Answer> ReadAnswerCSV() {
    std::vector<Answer> records;
    std::ifstream file(answer_csv);
    if (file) {
            std::string line;
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string aid, qid, choice_answer, judge_answer, subject_answer, mark;
                std::getline(ss, aid, ',');
                std::getline(ss, qid, ',');
                std::getline(ss, choice_answer, ',');
                std::getline(ss, judge_answer, ',');
                std::getline(ss, subject_answer, ',');
                std::getline(ss, mark, ',');
                // TODO
            }
    } else {
        perror("open answer csv.");
        exit(-1);
    }
    return records;
}
void WriteAnswerSheetCSV(std::vector<Answer> &) {

}

std::vector<AnswerSheet> ReadAnswerSheetCSV() {
    std::vector<AnswerSheet> records;
    std::ifstream file(answersheet_csv);
    if (file) {
            std::string line;
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string aid, pid, uid, total_mark;
                std::getline(ss, aid, ',');
                std::getline(ss, pid, ',');
                std::getline(ss, uid, ',');
                std::getline(ss, total_mark, ',');
                // TODO
            }
    } else {
        perror("open answer csv.");
        exit(-1);
    }
    return records;
}
void WriteAnswerSheetCSV(std::vector<AnswerSheet> &) {

}
