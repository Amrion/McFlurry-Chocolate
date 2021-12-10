#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WImage.h>
#include <Wt/WPushButton.h>
#include "Postgre_DB.h"
#include "User.hpp"
#include "TinderServer.hpp"

class ProfileWidget : public Wt::WContainerWidget {
public:
    ProfileWidget(Wt::WContainerWidget*, std::string, TinderServer&);
private:
    Wt::WImage* photo;
    Wt::WText* name;
    Wt::WText* sex;
    Wt::WText* discr;
    Wt::WText* age;
    Wt::WText* fac;
    Wt::WPushButton* back;

    TinderServer& server;

    void createInfoPage(Wt::WContainerWidget*, std::string);
};
