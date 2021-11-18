#pragma once
#include "DataBase.h"
#include <vector>

class photo {
    private:
    int length;
    int wight;
    vector <int> R;
    vector <int> G;
    vector <int> B;
    public:
    photo();
};

class PHOTOS : public Oracle_db {
    protected:
    string table = "PHOTOS";
  
    private:
    int _photoId;
    int _user_id;
    photo _photo;
    string _date;

    public:
    void setPhotoId(int id);
    int getPhotoId();

    void setUserId(int id);
    int getUserId();

    void setPhoto(photo _photo);
    photo getPhoto();

    void setDate(string date);
    string getDate();

    virtual int select_by_photoId();
    virtual int delete_by_photoId();
    virtual int save();
};