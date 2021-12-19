#pragma once
#include <iostream>
#include <string>
#include <pqxx/pqxx>
using namespace pqxx;

class DB {
  public:
    virtual int save(const std::string & table, std::vector <std::string> values, std::string where = "") = 0;
    virtual int update(const std::string & table, std::vector <std::string> values, std::string where = "") = 0;
    virtual int insert(const std::string & table, std::vector <std::string> values) = 0;
    virtual int delete_(const std::string & table, std::string where = "") = 0;
    virtual result select(const std::string table, std::string where = "", std::vector <std::string> what = std::vector <std::string>()) = 0;
};


