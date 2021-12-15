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
#include "TinderApplication.hpp"
#include "SearchPageWidget.h"
#include "PairWidget.h"
#include "UserWidget.h"
#include "TinderWidget.hpp"

class MainPageWidget : public Wt::WContainerWidget {
public:
    MainPageWidget(User&, TinderServer&, TinderApplication*, TinderWidget*);

    void creatPage (TinderApplication* app, TinderWidget* menu);

    void handleInternalPath(TinderApplication*);
private:
    Wt::WAnchor* userName;
    Wt::WImage* avatar;
    Wt::WText* pair;
    Wt::WAnchor* pairName;
    Wt::WImage* pairAvatar;
    Wt::WPushButton* start;
    Wt::WPushButton* exit;
    Wt::WContainerWidget* mainPageRight;

    UserWidget* userWidget;
    PairWidget* pairWidget;
    SearchPageWidget* searchPageWidget;

    User& user;
    TinderServer& server;
    Wt::WStackedWidget* wStackedWidget;

    std::vector<std::string> pairsLogin;
    std::vector<USERS_INFO> pairsInfo;

    void showSearchPhoto(TinderApplication*);
    void showInfoPair( const USERS_INFO&);
    void showInfoUser();
    void showLoginPage(TinderWidget*);
};
