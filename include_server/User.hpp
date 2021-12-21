#pragma once

#include <string>
#include <vector>

class User;

class User
{
public:
    User() = default;
    ~User() = default;

    std::string name;
    std::string surname;
    uint16_t age = 0;
    std::string gender;
    std::string faculty;
    uint16_t course_number = 0;
    std::string vk_link;
    std::string telegram_link;
    std::string description;
    uint16_t num_pairs = 0;
    std::vector <std::string> rec_users;
    std::vector <std::string> user_image;

    std::string username;
    std::string password;
};
