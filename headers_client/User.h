#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WImage.h>
#include <Wt/WPushButton.h>
#include <Wt/WStringStream.h>
#include <Wt/WBreak.h>
#include <Wt/WLineEdit.h>
#include <map>

class UserWidget : public Wt::WContainerWidget {
public:
    UserWidget(std::map<int, std::map<std::string, std::string>> data);
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