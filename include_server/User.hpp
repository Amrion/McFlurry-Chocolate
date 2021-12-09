#ifndef MCFLURRY_CHOCOLATE_USER_H
#define MCFLURRY_CHOCOLATE_USER_H

#include <string>
#include <vector>

class User;

class User
{
public:
    User();

    std::string name;
    std::string surname;
    int age;
    std::string gender;
    std::string faculty;
    int course_number;
    std::string vk_link;
    std::string telegram_link;
    std::string description;
    int num_pairs;
    std::vector <std::string> rec_users;
    std::vector <std::string> user_image;

    std::string username;
    std::string password;

    void kill() {
        this->~User();
    }
};

#endif //MCFLURRY_CHOCOLATE_USER_H