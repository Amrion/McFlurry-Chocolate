#ifndef PROJECT_INCLUDE_SERVER_TINDERWIDGET_HPP_
#define PROJECT_INCLUDE_SERVER_TINDERWIDGET_HPP_

#include <Wt/WContainerWidget.h>

#include "TinderServer.hpp"

class TinderWidget : public Wt::WContainerWidget {
public:
    explicit TinderWidget(TinderServer& server);
    ~TinderWidget() override;

    void letSignUp();
    void letLogin();

    void logout();

protected:
    bool loggedIn() const;

private:
    void signUp();
    void login();

private:
    TinderServer    &server_;

    bool                loggedIn_;
    User                user_;

    Wt::WLineEdit *userLoginEdit_;
    Wt::WLineEdit *passwordEdit_;
    Wt::WLineEdit *nameEdit_;
    Wt::WLineEdit *surnameEdit_;
    Wt::WLineEdit *confirmPasswordEdit_;
    Wt::WLineEdit *facultyEdit_;
    Wt::WLineEdit *courseNumberEdit_;
    Wt::WLineEdit *vkLinkEdit_;
    Wt::WLineEdit *telegramEdit_;
    Wt::WLineEdit *ageEdit_;
    Wt::WTextArea *descriptionEdit_;
    Wt::WButtonGroup *genderBtn_;
    Wt::WButtonGroup *soulMateGenderBtn_;

    Wt::WText     *statusMsg_;

    typedef Wt::Core::observing_ptr<Wt::WPushButton> ButtonPtr;
};


#endif  // PROJECT_INCLUDE_SERVER_TINDERWIDGET_HPP_