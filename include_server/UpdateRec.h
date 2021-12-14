#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

#include "Postgre_DB.h"

class UpdateManager
{
public:
    explicit UpdateManager(Postgre_DB &db) : db_(db) {}

private:
    Postgre_DB db_;
    static std::atomic<int> now_;
    static std::atomic<bool> stop_;

    struct update_thread : private std::thread {
        ~update_thread();
        update_thread(update_thread&&) = default;

        using std::thread::thread;
    };

public:
    update_thread start();
};

void update(Postgre_DB &db);