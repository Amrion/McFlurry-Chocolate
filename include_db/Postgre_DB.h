#pragma once
#include "DataBase.h"
#include "TABLES.h"
#include "recsys.hpp"
#include "dirent.h"
#include <fstream>
#include <memory>
#include <list>

class Postgre_DB : DB {
    private:
        std::shared_ptr <connection> PG_conn;
        
        virtual int save(const std::string & table, std::vector <std::string> values, std::string where = "") override;
        virtual int update(const std::string & table, std::vector <std::string> values, std::string where = "") override;
        virtual int insert(const std::string & table, std::vector <std::string> values) override;
        virtual int delete_(const std::string & table, std::string where = "") override;
        virtual result select(const std::string table, std::string where = "", std::vector <std::string> what = std::vector <std::string>()) override;
        int max_id(const std::string & table, std::string name_id);
        int init_tables();
        std::vector <std::vector<float>> users_params();
        std::vector <std::vector <int>> marks_matrix();
        std::string remove_danger_characters(const std::string & row_column);
        
    public:
        Postgre_DB(std::string host, std::string port, std::string db_name, std::string user, std::string password);
        ~Postgre_DB();
        int drop_tables();
        
        int user_id(std::string login);
        std::string user_login(int id);

        int user_register(std::string login, std::string password); 
        int save_user(USERS_INFO user_info);
        USERS_INFO user_info(std::string login);
        int user_exist(std::string login, std::string password = "");

        int set_mark(std::string login_marker, std::string login_marked, int mark);
        std::vector <std::string> pairs_login(std::string login);
        int gender_is_different(int id1, int id2);
        int is_pair(int id1, int id2);
        int seen(int id1, int id2);

        int make_recommendations();
        std::vector <std::string> user_rec(std::string login);

        int save_image(std::string path_to_file, int user_id, std::string name = "");
        std::vector <std::string> user_image(int user_id, std::string image_name = "");
        int delete_image(int user_id, std::string image_name = "");
};