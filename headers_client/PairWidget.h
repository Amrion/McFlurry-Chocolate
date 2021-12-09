#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WImage.h>
#include <Wt/WPushButton.h>

#include "User.hpp"
#include "Postgre_DB.h"

class PairWidget : public Wt::WContainerWidget {
public:
    PairWidget(Wt::WContainerWidget*, const USERS_INFO&);
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

    void createInfoPage(Wt::WContainerWidget*, const USERS_INFO&);
};
