#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WImage.h>
#include <Wt/WLink.h>
#include <Wt/WPushButton.h>
#include <Wt/WStringStream.h>
#include <Wt/WBreak.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WWidget.h>
#include  <Wt/WAnchor.h>
#include <Wt/WBorderLayout.h>

#include "../server_temp/TinderServer.h"

class MainPageWidget : public Wt::WContainerWidget {
public:
    MainPageWidget(std::map<std::string, std::string> data, TinderServer& server);

protected:
    Wt::WImage* photo;
    Wt::WPushButton* like;
    Wt::WPushButton* back;
    Wt::WPushButton* forward;
    Wt::WPushButton* dislike;
    Wt::WAnchor* name;
    Wt::WPushButton* info;
    Wt::WImage* avatar;
    Wt::WText* pair;
    Wt::WAnchor* pairName;
    Wt::WImage* pairAvatar;

    TinderServer& server;
private:
    std::map<std::string, std::string> data;

    void changePhoto(Wt::WContainerWidget*);
    void changePhototemp(Wt::WContainerWidget*);

};
