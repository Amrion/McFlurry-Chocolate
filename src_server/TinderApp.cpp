#include <Wt/WAnchor.h>
#include <Wt/WText.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WApplication.h>
#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/RegistrationModel.h>

#include "TinderApp.h"

TinderApp::TinderApp():
        WContainerWidget(),
        mainPage(0)
{
    session_.login().changed().connect(this, &TinderApp::onAuthEvent);

    std::unique_ptr<Auth::AuthModel> authModel
            = std::make_unique<Auth::AuthModel>(Session::auth(), session_.users());
    authModel->addPasswordAuth(&Session::passwordAuth());
    authModel->addOAuth(Session::oAuth());

    std::unique_ptr<Auth::AuthWidget> authWidget
            = std::make_unique<Auth::AuthWidget>(session_.login());
    auto authWidgetPtr = authWidget.get();
    authWidget->setModel(std::move(authModel));
    authWidget->setRegistrationEnabled(true);

    std::unique_ptr<WText> title(std::make_unique<WText>("<h1>BMSTU Tinder</h1>"));
    addWidget(std::move(title));

    addWidget(std::move(authWidget));

    mainStack_ = new WStackedWidget();
    mainStack_->setStyleClass("appstack");
    addWidget(std::unique_ptr<WStackedWidget>(mainStack_));

    links_ = new WContainerWidget();
    links_->setStyleClass("links");
    links_->hide();
    addWidget(std::unique_ptr<WContainerWidget>(links_));

    backToAppAnchor_ = links_->addWidget(std::make_unique<WAnchor>("/app", "Tinder App"));
    backToAppAnchor_->setLink(WLink(LinkType::InternalPath, "/app"));

    settingsAnchor_ = links_->addWidget(std::make_unique<WAnchor>("/settings", "Settings"));
    settingsAnchor_->setLink(WLink(LinkType::InternalPath, "/settings"));

    WApplication::instance()->internalPathChanged()
            .connect(this, &TinderApp::handleInternalPath);

    authWidgetPtr->processEnvironment();
}

void TinderApp::onAuthEvent()
{
    if (session_.login().loggedIn()) {
        links_->show();
        handleInternalPath(WApplication::instance()->internalPath());
    } else {
        mainStack_->clear();
        mainPage = 0;
        links_->hide();
    }
}

void TinderApp::handleInternalPath(const std::string &internalPath)
{
    if (session_.login().loggedIn()) {
        if (internalPath == "/app")
            showMainPage();
        else if (internalPath == "/settings")
            showSettings();
        else
            WApplication::instance()->setInternalPath("/app",  true);
    }
}

void TinderApp::showSettings()
{

    backToAppAnchor_->removeStyleClass("selected-link");
    settingsAnchor_->addStyleClass("selected-link");
}

void TinderApp::showMainPage()
{

    backToAppAnchor_->addStyleClass("selected-link");
    settingsAnchor_->removeStyleClass("selected-link");
}