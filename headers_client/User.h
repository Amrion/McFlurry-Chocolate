#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WImage.h>
#include <Wt/WPushButton.h>
#include <Wt/WStringStream.h>
#include <Wt/WBreak.h>
#include <Wt/WLineEdit.h>

class User : public Wt::WContainerWidget {
public:
    User(Wt::WStringStream data);
private:
    Wt::WImage photo;
    Wt::WPushButton changeData;
    Wt::WPushButton addPhoto;
    Wt::WPushButton saveData;
    Wt::WText name;
    Wt::WText discText;
    Wt::WTextArea discEdit;
    Wt::WText ageText;
    Wt::WLineEdit ageEdit;
    Wt::WText netText;
    Wt::WLineEdit netEdit;
    Wt::WImage logo;
};