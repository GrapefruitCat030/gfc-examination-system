#include "answerbank_service.h"


AnswerBankService::AnswerBankService(DataBaseService *, LogService *) {}

// Teacher Interface
void AnswerBankService::ViewAnswerList() {};
void AnswerBankService::ChooseAnswer() {};
void AnswerBankService::CorrectAnswer() {};
// Student Interface
void AnswerBankService::StartAnswer() {};
AnswerSheet AnswerBankService::ViewResult() {
    return AnswerSheet{};
};