#pragma once 
#include <vector>
#include <string>
using namespace std;

struct USERS_INFO {
    int user_id;
    string name;
    string surname;
    uint8_t age;
    string gender;
    string faculty;
    uint8_t course_number;
    string vk_link;
    string telegram_link;
    uint32_t num_pairs;
    string description;
    USERS_INFO();
};



