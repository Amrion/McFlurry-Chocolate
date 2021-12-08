#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WImage.h>
#include <Wt/WPushButton.h>

class ProfileWidget : public Wt::WContainerWidget {
public:
    explicit ProfileWidget(Wt::WContainerWidget*);
private:
    Wt::WImage* photo;
    Wt::WText* name;
    Wt::WText* sex;
    Wt::WText* discr;
    Wt::WText* age;
    Wt::WText* fac;
    Wt::WPushButton* back;

    void createInfoPage(Wt::WContainerWidget*);
};
