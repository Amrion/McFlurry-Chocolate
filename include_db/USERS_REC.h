#pragma once
#include "DataBase.h"
#include "marks.h"
#include "recsys.hpp"

using namespace std;

class USERS_REC : public Oracle_db {
  protected:
  string table = "USERS_REC";
  
  private:
  int _id;
  vector <int> _id_rec;

  map create_rec_map();
  vector <vector <int>> map_into_vector();
  public:

  void setId(const int id);
  int getId();

  void setId_rec(const vector <int> users_rec);
  vector <int> GetId_rec();

  void new_recomendations();
  virtual int select_by_id();
  virtual int delete_by_id();
};

