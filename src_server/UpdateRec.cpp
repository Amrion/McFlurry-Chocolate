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
                             auto next = system_clock::now() + 1min;
                             while (!stop_) {
                                 this_thread::sleep_until(next);
                                 update(db_);
                                 next += 1min;
                             }
                         }};
}

void update(Postgre_DB &db) {
    db.make_recommendations();
}