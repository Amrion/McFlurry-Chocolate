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

class SearchPageWidget : public Wt::WContainerWidget {
public:
    explicit SearchPageWidget(Wt::WContainerWidget*);
private:
    Wt::WPushButton* like;
    Wt::WPushButton* back;
    Wt::WPushButton* forward;
    Wt::WPushButton* dislike;
    Wt::WImage* photo;
    Wt::WPushButton* info;

    void createSearchPage(Wt::WContainerWidget*);

    void changePhoto(Wt::WContainerWidget*);
    void changePhototemp(Wt::WContainerWidget*);
};