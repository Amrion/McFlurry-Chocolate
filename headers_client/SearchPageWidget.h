#pragma once

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WImage.h>
#include <Wt/WLink.h>
#include <Wt/WPushButton.h>
#include <Wt/WStringStream.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WWidget.h>
#include  <Wt/WAnchor.h>

#include "Postgre_DB.h"
#include "User.hpp"
#include "TinderServer.hpp"

class SearchPageWidget : public Wt::WContainerWidget {
public:
    SearchPageWidget(Wt::WContainerWidget*, User&, TinderServer&);
private:
    Wt::WPushButton* like;
    Wt::WPushButton* back;
    Wt::WPushButton* forward;
    Wt::WPushButton* dislike;
    Wt::WImage* photo;
    Wt::WPushButton* info;

    Wt::WImage* photoProf;
    Wt::WText* name;
    Wt::WText* sex;
    Wt::WText* discr;
    Wt::WText* age;
    Wt::WText* fac;
    Wt::WPushButton* backSearch;

    User& user;
    TinderServer& server;

    size_t number;
    size_t kol;
    std::vector<std::string> photoes;

    void createSearchPage(Wt::WContainerWidget*);

    void showInfoProfile(Wt::WContainerWidget*);

    void changeMan(Wt::WContainerWidget*, Wt::WContainerWidget*);

    void changePhotoForward(Wt::WContainerWidget*);
    void changePhotoBack(Wt::WContainerWidget*);
};