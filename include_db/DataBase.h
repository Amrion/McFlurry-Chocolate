#pragma once
#include <iostream>
#include <string>
using namespace std;

class DB {
  public:
  virtual int connect(string host, string user, string password) = 0;
  virtual DB * select(string & where, string & order_by) = 0;
  virtual int update(string & where) = 0;
  virtual int insert() = 0;
  virtual int save() = 0;
  virtual int delete_(string & where) = 0;
  virtual int close_connection() = 0;
  virtual int max_id() = 0;
};


class Oracle_db : public DB {
  private:
  string table;
  public:
  virtual int connect(string host, string user, string password) override;
  virtual DB * select(string & where, string & order_by) override;
  virtual int update(string & where) override;
  virtual int insert() override;
  virtual int save() override;
  virtual int delete_(string & where) override;
  virtual int close_connection() override;
  virtual int max_id() override;
};