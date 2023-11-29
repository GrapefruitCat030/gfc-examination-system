#include "examsystem_service.h"
#include "database_service.h"
#include "log_service.h"


int main() {
    DataBaseService db_service;
    LogService      log_service;
    ExamSystemService examsystem_service(&db_service, &log_service);
    examsystem_service.BootService();
}