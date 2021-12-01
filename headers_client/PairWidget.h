#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WImage.h>
#include <Wt/WPushButton.h>

class PairWidget : public Wt::WContainerWidget {
public:
    explicit PairWidget(Wt::WContainerWidget*);
private:
    Wt::WImage* photo;
    Wt::WText* name;
    Wt::WText* discr;
    Wt::WText* age;
    Wt::WAnchor* net;
    Wt::WPushButton* back;

    void createInfoPage(Wt::WContainerWidget*);
};
