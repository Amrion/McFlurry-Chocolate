#pragma once 
#include <vector>
#include <string>
using namespace std;

struct LOGIN {
    int user_id;
    string login;
    double password;
};

struct USERS_INFO {
    int user_id;
    string name;
    string surname;
    int age;
    string gender;
    string faculty;
    int course_number;
    string vk_link;
    string telegram_link;
    int num_pairs;
    string description;
    string soul_mate_gender; 
    USERS_INFO();
};

struct USERS_REC {
    int user_id;
    std::vector <int> id_rec_users;
};

struct MARKS {
    int mark_id;
    int user_id_marker;
    int user_id_marked;
    int mark;
};

struct IMAGES {
    int image_id;
    int user_id;
    string image;
};

