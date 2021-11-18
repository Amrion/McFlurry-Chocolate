#pragma once
#include "DataBase.h"
#include <vector>

class MARKS : public Oracle_db {
  protected:
  string table = "MARKS";

  private:
  int _markId;
  int _id;
  int _id_other;
  int _mark;
  string _date;

  public:
  void setMarkId(int id);
  int getMarkId();

  void setIdFirstUser(int id);
  int getIdFirstUser();

  void setIdSecondUser(int id_other);
  int getIdSecondUser();

  void setMark(int mark);
  int getMark();

  void setDate(string date);
  string getDate();

  vector <vector <int>> create_matrix_marks();
  virtual int select_by_id();
  virtual int delete_by_id();
};