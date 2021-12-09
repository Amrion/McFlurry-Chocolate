#pragma once

#include <map>
#include <thread>
#include <mutex>

#include "User.hpp"
#include "Postgre_DB.h"


class TinderServer {
public:

    explicit TinderServer(Wt::WServer& server, const Postgre_DB &db);

    TinderServer(const TinderServer &) = delete;
    TinderServer &operator=(const TinderServer &) = delete;

    bool signUp(User& user);
    bool login(User& user);
    void logout(User &user);

    Postgre_DB getBd() const {
        return db_;
    }

private:
    Wt::WServer&            server_;
    std::recursive_mutex    mutex_;
    Postgre_DB db_;

    User user_;
};