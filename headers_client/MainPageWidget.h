#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WImage.h>
#include <Wt/WLink.h>
#include <Wt/WPushButton.h>
#include <Wt/WStringStream.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WWidget.h>
#include  <Wt/WAnchor.h>

#include "User.hpp"
#include "Postgre_DB.h"
#include "TinderServer.hpp"
#include "ProfileWidget.h"
#include "TinderApplication.hpp"
#include "SearchPageWidget.h"
#include "PairWidget.h"
#include "UserWidget.h"

class MainPageWidget : public Wt::WContainerWidget {
public:
    MainPageWidget(User&, TinderServer&, TinderApplication*);

    void handleInternalPath(TinderApplication*, Wt::WContainerWidget*, std::vector<USERS_INFO>);
private:
    Wt::WAnchor* userName;
    Wt::WImage* avatar;
    Wt::WText* pair;
    Wt::WAnchor* pairName;
    Wt::WImage* pairAvatar;
    Wt::WPushButton* start;
    Wt::WPushButton* exit;

    ProfileWidget* profileWidget;
    UserWidget* userWidget;
    PairWidget* pairWidget;
    SearchPageWidget* searchPageWidget;

    User& user;
    TinderServer& server;
    Wt::WStackedWidget* wStackedWidget;
    std::map<std::string, std::string> data;

    void showSearchPhoto(Wt::WContainerWidget*);
    void showInfoPair(Wt::WContainerWidget*, const USERS_INFO&);
    void showInfoProfile(Wt::WContainerWidget*, const std::string&);
    void showInfoUser(Wt::WContainerWidget*);
};
