#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WImage.h>
#include <Wt/WPushButton.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTextArea.h>
#include <Wt/WIntValidator.h>
#include <Wt/WFileUpload.h>
#include <stack>

#include "Postgre_DB.h"
#include "User.hpp"
#include "TinderServer.hpp"

class UserWidget : public Wt::WContainerWidget {
public:
    explicit UserWidget(Wt::WContainerWidget*, User&, TinderServer&);
private:
    Wt::WImage* myPhoto;
    Wt::WPushButton* deletePhoto;
    Wt::WFileUpload* addPhoto;
    Wt::WPushButton* savePhoto;
    Wt::WPushButton* saveData;
    Wt::WPushButton* back;
    Wt::WText* discText;
    Wt::WTextArea* discEdit;
    Wt::WText* nameText;
    Wt::WLineEdit* nameEdit;
    Wt::WText* ageText;
    Wt::WLineEdit* ageEdit;
    Wt::WText* facText;
    Wt::WLineEdit* facEdit;
    Wt::WText* courseText;
    Wt::WLineEdit* courseEdit;
    Wt::WText* tgText;
    Wt::WLineEdit* tgEdit;
    Wt::WText* netText;
    Wt::WLineEdit* netEdit;


    User& user;
    TinderServer& server;

    void createInfoPage(Wt::WContainerWidget*);
};