#pragma once

#include<string>

// enum CourseType {
//    kSubjectPython = 0,
//    kSubjectCpp, 
// };
// const std::string CourseName[4] = {
//     "python",
//     "cpp",
//     "golang",
//     "ics"
// };

enum QuestionType {
    kQuestionTypeChoice = 0,
    kQuestionTypeJudge,
    kQuestionTypeSubject,
};

const std::string QuestionTypeStr[3] = {
    "Choice",
    "Judge",
    "Subject"
};
