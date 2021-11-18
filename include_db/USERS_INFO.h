#pragma once
#include <vector>
#include "DataBase.h"
using namespace std;

class USERS_INFO : public Oracle_db {
  protected:
  string table = "USERS_INFO";
  
  private:
  int _id;
  string _mail;
  double _password;
  string _name;
  string _surname;
  int _age;
  string _gender;
  string _faculty;
  int _course_number;
  string _vk_link;
  string _telegram_link;

  public:
  USERS_INFO(string Host, string User, string Password);

  void setId(const int id);
  int getId();

  void setMail(const string mail);
  string getMail();

  void setPassword(const double password);
  double getPassword();

  void setName(const string name);
  string getName();

  void setSurname(const string surname);
  string getSurname();

  void setAge(const int age);
  int getAge();

  void setGender(const string gender);
  string getGender();

  void setFaculty(const string faculty);
  string getFaculty();

  void setCourse_number(const int course_number);
  int getCourse_number();

  void setVk_link(const string vk_link);
  string getVk_link();

  void setTelegram_link(const string telegram_link);
  string getTelegram_link();


  virtual int select_by_id();
  virtual int delete_by_id();
};