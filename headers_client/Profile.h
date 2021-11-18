#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WImage.h>
#include <Wt/WPushButton.h>
#include <Wt/WStringStream.h>
#include <Wt/WBreak.h>

class Profile : public Wt::WContainerWidget {
public:
    Profile(Wt::WStringStream data);
private:
    Wt::WImage photo;
    Wt::WText name;
    Wt::WText discr;
    Wt::WText age;
    Wt::WText net;
    Wt::WImage logo;
    Wt::WImage avatar;
    Wt::WText pair;
    Wt::WText pairName;
    Wt::WImage pairAvatar;
};
