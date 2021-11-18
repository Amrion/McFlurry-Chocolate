#pragma once
#include "DataBase.h"
class DIALOGS : public Oracle_db {
    protected:
    string table = "DIALOGS";

    private:
    int dialog_id;
    int dialog_one_user_id;
    int dialog_two_user_id;
    string _date;

    public:
    void setDialog_id(int id);
    int getDialog_id();

    void setFirstUserId(int id);
    int getFirstUserId();

    void setSecondUserId(int id);
    int getSecondUserId();

    void setDate(string date);
    string getDate();

    virtual int select_by_dialogId();
    virtual int delete_by_dialogId();
    virtual int save();
};

class MESSAGES : public Oracle_db {
    protected:
    string table = "MESSAGES";

    private:
    int msg_id;
    string msg_text;
    int dialog_id;
    int user1_id;
    int user2_id;
    string msg_time;
    public:
    void setMId(int id);
    int getMId();

    void setText(string text);
    string getText();

    void setDialogId(int id);
    int getDialogId();

    void setSendinUserId(int id);
    int getSendinUserId();

    void setReceivingUserId(int id);
    int getReceivingUserId();

    void setDate(string date);
    string getDate();

    virtual int select_by_messageId();
    virtual int delete_by_messageId();
    virtual int save();
};