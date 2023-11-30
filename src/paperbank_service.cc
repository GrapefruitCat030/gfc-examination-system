#include"paperbank_service.h"

PaperBankService::PaperBankService(DataBaseService *, LogService *) {

}
PaperBankService::~PaperBankService() {

}

void       PaperBankService::ViewPaperList() {}
Paper      PaperBankService::CreatePaper() {
    return Paper{};
}
void       PaperBankService::AddPaper() {}