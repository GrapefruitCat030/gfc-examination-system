
#include "examsystem_service.h"

#include<memory>
#include<assert.h>


ExamSystemService::ExamSystemService(DataBaseService *dbs, LogService *lgs) :
                    authentic_(dbs, lgs) {
    db_service_ = dbs;
    log_service_ = lgs;
}

void ExamSystemService::BootService() {
    User basic_user = authentic_.Login();
    
    int rc = basic_user.authority_;
    if(rc == 0)         user_ = new Admin(basic_user, db_service_, log_service_);
    else if (rc == 1)   user_ = new Teacher(db_service_, log_service_, kSubjectPython);
    else if (rc == 2)   user_ = new Student(db_service_, log_service_);
    else assert(0); 


    user_->BootService(); // TODO: check the function whether truly call Admin function.
} 

