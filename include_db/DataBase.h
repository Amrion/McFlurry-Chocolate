#pragma once
#include <iostream>
#include <string>
#include <pqxx/pqxx>
using namespace std;
using namespace pqxx;

class DB {
  public:
    virtual int save(const string & table, std::vector <string> values, string where = "") = 0;
    virtual int update(const string & table, std::vector <string> values, string where = "") = 0;
    virtual int insert(const string & table, std::vector <string> values) = 0;
    virtual int delete_(const string & table, string where = "") = 0;
};


