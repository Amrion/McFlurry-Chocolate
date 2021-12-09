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

class SearchPageWidget : public Wt::WContainerWidget {
public:
    SearchPageWidget(Wt::WContainerWidget*, User&, const Postgre_DB& db);
private:
    Wt::WPushButton* like;
    Wt::WPushButton* back;
    Wt::WPushButton* forward;
    Wt::WPushButton* dislike;
    Wt::WImage* photo;
    Wt::WPushButton* info;

    User& user;

    void createSearchPage(Wt::WContainerWidget*, Postgre_DB db);

    void changePhoto(Wt::WContainerWidget*, std::vector<std::string>::iterator, Postgre_DB db);
};