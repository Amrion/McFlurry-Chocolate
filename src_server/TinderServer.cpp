#include <Wt/WServer.h>

#include "TinderServer.hpp"
#include "md5.h"


TinderServer::TinderServer(Wt::WServer &server, const Postgre_DB &db)
        : server_(server), db_(db) {
}

bool TinderServer::signUp(User &user) {
    std::unique_lock<std::recursive_mutex> lock(mutex_);
    USERS_INFO usersInfo;
    usersInfo.user_id = db_.user_register(user.username, md5(user.password));
    if (usersInfo.user_id) {
        usersInfo.name = user.name;
        usersInfo.surname = user.surname;
        usersInfo.age = user.age;
        usersInfo.gender = user.gender;
        usersInfo.faculty = user.faculty;
        usersInfo.course_number = user.course_number;
        usersInfo.vk_link = user.vk_link;
        usersInfo.telegram_link = user.telegram_link;
        usersInfo.description = user.description;
        usersInfo.soul_mate_gender = user.soulMateGender;
        //db_.save_image();
        db_.save_user(usersInfo);
        return true;
    }
    return false;
}

bool TinderServer::login(User &user) {
    std::unique_lock<std::recursive_mutex> lock(mutex_);
    if (db_.user_exist(user.username, md5(user.password))) {
        USERS_INFO usersInfo;
        usersInfo = db_.user_info(user.username);
        user.name = usersInfo.name;
        user.surname = usersInfo.surname;
        user.age = usersInfo.age;
        user.gender = usersInfo.gender;
        user.faculty = usersInfo.faculty;
        user.course_number = usersInfo.course_number;
        user.vk_link = usersInfo.vk_link;
        user.telegram_link = usersInfo.telegram_link;
        user.description = usersInfo.description;
        user.soulMateGender = usersInfo.soul_mate_gender;
        //user.rec_users
        //user.image
        return true;
    }
    return false;
}

void TinderServer::logout(User &user) {
    std::unique_lock<std::recursive_mutex> lock(mutex_);
    user.kill();
}