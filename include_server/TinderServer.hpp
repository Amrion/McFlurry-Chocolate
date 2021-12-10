#pragma once

#include <map>
#include <thread>
#include <mutex>

#include "User.hpp"
#include "Postgre_DB.h"


class TinderServer {
public:

    explicit TinderServer(Wt::WServer& server, Postgre_DB &db);

    TinderServer(const TinderServer &) = delete;
    TinderServer &operator=(const TinderServer &) = delete;

    bool signUp(User& user);
    bool login(User& user);
    void logout(User &user);

    Postgre_DB db_;

private:
    Wt::WServer&            server_;
    std::recursive_mutex    mutex_;


    User user_;
};