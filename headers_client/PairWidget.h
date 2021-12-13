#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WImage.h>
#include <Wt/WPushButton.h>

#include "User.hpp"
#include "Postgre_DB.h"
#include "TinderServer.hpp"

class PairWidget : public Wt::WContainerWidget {
public:
    PairWidget(Wt::WContainerWidget*, const USERS_INFO&, TinderServer&);
private:
    Wt::WImage* photo;
    Wt::WText* name;
    Wt::WText* discr;
    Wt::WText* age;
    Wt::WText* sex;
    Wt::WText* fac;
    Wt::WAnchor* tg;
    Wt::WAnchor* net;
    Wt::WPushButton* back;

    TinderServer& server;

    void createInfoPage(Wt::WContainerWidget*, const USERS_INFO&);
};
