#include "UpdateRec.h"

std::atomic<int>  UpdateManager::now_{0};
std::atomic<bool> UpdateManager::stop_{false};

UpdateManager::update_thread::~update_thread() {
    if (joinable()) {
        stop_ = true;
        join();
    }
}

UpdateManager::update_thread UpdateManager::start() {
    return update_thread{[this]{
                             using namespace std;
                             using namespace std::chrono;
                             auto next = system_clock::now() + 5s;
                             while (!stop_) {
                                 this_thread::sleep_until(next);
                                 update(db_);
                                 next += 5s;
                             }
                         }};
}

void update(Postgre_DB &db) {
    std::cout << "1111111111111111" << std::endl;
//    std::vector<string> user_rec;
    db.make_recommendations();
//    user_rec = db.user_rec("w");
//    for (std::vector<string>::iterator i = user_rec.begin(); i != user_rec.end(); ++i) {
//        std::cout << *i << " ";
//    }
}