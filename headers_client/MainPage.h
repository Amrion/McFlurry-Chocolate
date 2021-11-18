#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WImage.h>
#include <Wt/WPushButton.h>
#include <Wt/WStringStream.h>
#include <Wt/WBreak.h>

class MainPage : public Wt::WContainerWidget {
public:
    MainPage(Wt::WStringStream data);
private:
    Wt::WImage photo;
    Wt::WPushButton like;
    Wt::WPushButton dislike;
    Wt::WText name;
    Wt::WText discr;
    Wt::WText age;
    Wt::WImage logo;
    Wt::WImage avatar;
    Wt::WText pair;
    Wt::WText pairName;
    Wt::WImage pairAvatar;
};
