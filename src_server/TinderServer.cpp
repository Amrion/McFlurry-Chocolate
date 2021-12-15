#include <cstdlib>
#include <filesystem>
#include <Wt/WServer.h>
#include <Wt/WFileResource.h>

#include "TinderServer.hpp"
#include "md5.h"

TinderServer::TinderServer(Wt::WServer &server, Postgre_DB &db)
        : db_(db), server_(server) {
}

bool TinderServer::signUp(User &user) {
    std::unique_lock<std::recursive_mutex> lock(mutex_);
    USERS_INFO usersInfo;
    usersInfo.user_id = db_.user_register(user.username, md5(user.password));
    if (usersInfo.user_id >= 0) {
        usersInfo.name = user.name;
        usersInfo.surname = user.surname;
        usersInfo.age = user.age;
        usersInfo.gender = user.gender;
        usersInfo.faculty = user.faculty;
        usersInfo.course_number = user.course_number;
        usersInfo.vk_link = user.vk_link;
        usersInfo.telegram_link = user.telegram_link;
        usersInfo.description = user.description;

        auto end = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        std::string time = std::ctime(&end_time);
        time.erase(std::remove(time.begin(),time.end(),' '),time.end());

        std::string command = "mkdir -p ../users_images";
        system(command.c_str());
        command = "mv " + user.user_image[0] + " ../users_images";
        system(command.c_str());
        std::filesystem::path p(user.user_image[0]);
        command = "mv ../users_images/" + string(p.stem()) + " ../users_images/profilePhoto" + std::to_string(usersInfo.user_id) + time;
        system(command.c_str());
        user.user_image[0] = "../users_images/profilePhoto" + std::to_string(usersInfo.user_id) + time;
        db_.save_image("../users_images/profilePhoto" + std::to_string(usersInfo.user_id) + time, usersInfo.user_id, "profilePhoto" + std::to_string(usersInfo.user_id) + time);
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
        user.num_pairs = usersInfo.num_pairs;
        user.vk_link = usersInfo.vk_link;
        user.telegram_link = usersInfo.telegram_link;
        user.description = usersInfo.description;
        user.rec_users = db_.user_rec(user.username);
        user.user_image = db_.user_image(db_.user_id(user.username));
        return true;
    }
    return false;
}

void TinderServer::logout(User &user) {
    std::unique_lock<std::recursive_mutex> lock(mutex_);
//    user.kill();
}