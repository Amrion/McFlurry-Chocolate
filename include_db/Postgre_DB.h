#pragma once
#include "DataBase.h"
#include "TABLES.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "recsys.hpp"
#include "base64.h"
#include "dirent.h"

class Postgre_DB : DB {
    private:
        connection * PG_conn;
        virtual int save(const string & table, std::vector <string> values, string where = "") override;
        virtual int update(const string & table, std::vector <string> values, string where = "") override;
        virtual int insert(const string & table, std::vector <string> values) override;
        virtual int delete_(const string & table, string where = "") override;
        int max_id(const string & table, string name_id);
    public:
        Postgre_DB(string host, string port, string db_name, string user, string password);
        ~Postgre_DB();
        int init_tables();
        int drop_tables();
        int user_exist(string login, float password = -1);
        int user_register(string login, float password); 
        int user_id(string login);
        string user_login(int id);
        int save_user(USERS_INFO user_info);
        USERS_INFO user_info(string login);
        int set_mark(string login_marker, string login_marked, int mark);
        std::vector <string> pairs_login(string login);
        std::vector <std::vector <int>> marks_matrix();
        int gender_is_different(int id1, int id2);
        int is_pair(int id1, int id2);
        int seen(int id1, int id2);
        int make_recommendations();
        std::vector <string> user_rec(string login);
        int save_image(string path_to_file, int user_id, string name);
        std::vector <string> user_image(string dirname, int user_id, string image_name = "");
        
};