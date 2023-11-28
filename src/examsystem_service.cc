
#include "examsystem_service.h"

ExamSystemService::ExamSystemService(DataBaseService *dbs, LogService *lgs) :
                    authentic_(dbs, lgs) {
    db_service_ = dbs;
    log_service_ = lgs;
}

void ExamSystemService::boot_service() {
    int rc = authentic_.Login();
    switch (rc) {
    case 0:
        Admin user(db_service_, log_service_);
        break;
    case 1:
        break;
    case 2:
        break;
    default:
        break;
    }
} 

