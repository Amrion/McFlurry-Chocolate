#ifndef PROJECT_INCLUDE_SERVER_TINDERSERVER_HPP_
#define PROJECT_INCLUDE_SERVER_TINDERSERVER_HPP_


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
    void logout(const User &user);

private:
    Wt::WServer&            server_;
    std::recursive_mutex    mutex_;
    Postgre_DB db_;

    User user_;
};


#endif  // PROJECT_INCLUDE_SERVER_TINDERSERVER_HPP_
