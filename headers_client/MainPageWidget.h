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

#include "TinderServer.hpp"
#include "ProfileWidget.h"
#include "TinderApplication.hpp"
#include "SearchPageWidget.h"
#include "PairWidget.h"
#include "UserWidget.h"

class MainPageWidget : public Wt::WContainerWidget {
public:
    MainPageWidget(TinderServer&, TinderApplication*);

    void handleInternalPath(TinderApplication*, Wt::WContainerWidget*);
private:
    Wt::WAnchor* name;
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

    TinderServer& server;
    Wt::WStackedWidget* wStackedWidget;
    std::map<std::string, std::string> data;

    void showSearchPhoto(Wt::WContainerWidget*);
    void showInfoPair(Wt::WContainerWidget*);
    void showInfoProfile(Wt::WContainerWidget*);
    void showInfoUser(Wt::WContainerWidget*);
};
