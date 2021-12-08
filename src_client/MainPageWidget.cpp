#include "MainPageWidget.h"
#include "TinderServer.hpp"

MainPageWidget::MainPageWidget(TinderServer& server, TinderApplication* app)
    : server(server) {
    auto mainPage = addWidget(std::make_unique<Wt::WContainerWidget>());
    mainPage->setStyleClass("page");
    auto mainPageLeft = mainPage->addWidget(std::make_unique<Wt::WContainerWidget>());
    mainPageLeft->setStyleClass("me");
    auto mainPageRight = mainPage->addWidget(std::make_unique<Wt::WContainerWidget>());
    mainPageRight->setStyleClass("people");

    auto myNameWidget = mainPageLeft->addWidget(std::make_unique<Wt::WContainerWidget>());
    myNameWidget->setStyleClass("myName");

    avatar = myNameWidget->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("../css/Me.jpg")));
    avatar->setStyleClass("avatar");

    Wt::WLink link = Wt::WLink("/user");
    name = myNameWidget->addWidget(std::make_unique<Wt::WAnchor>(link, "Даниил"));
    name->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/user"));
    name->setStyleClass("name");

    exit = myNameWidget->addWidget(std::make_unique<Wt::WPushButton>("Выйти"));
    exit->setStyleClass("exit");
    exit->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/"));

    auto pWidget = mainPageLeft->addWidget(std::make_unique<Wt::WContainerWidget>());
    pWidget->setStyleClass("pair");
    pair = pWidget->addWidget(std::make_unique<Wt::WText>("Пары"));
    pair->setStyleClass("pairText");

    auto pairAvatarWidgetFirst = mainPageLeft->addWidget(std::make_unique<Wt::WContainerWidget>());
    pairAvatarWidgetFirst->setStyleClass("pairDiv");

    link = Wt::WLink("/pair");
    pairName = pairAvatarWidgetFirst->addWidget(std::make_unique<Wt::WAnchor>(link, "Оля"));
    pairName->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/pair"));
    pairName->setStyleClass("pairName");

    pairAvatar = pairAvatarWidgetFirst->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("../css/pair1.jpg")));
    pairAvatar->setStyleClass("pairAvatar");

    link = Wt::WLink("/pair");
    pairName = pairAvatarWidgetFirst->addWidget(std::make_unique<Wt::WAnchor>(link, "Арина"));
    pairName->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/pair"));
    pairName->setStyleClass("pairName");

    pairAvatar = pairAvatarWidgetFirst->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("../css/pair2.jpg")));
    pairAvatar->setStyleClass("pairAvatar");

    auto pairAvatarWidgetSecond = mainPageLeft->addWidget(std::make_unique<Wt::WContainerWidget>());
    pairAvatarWidgetSecond->setStyleClass("pairDiv");

    link = Wt::WLink("/pair");
    pairName = pairAvatarWidgetSecond->addWidget(std::make_unique<Wt::WAnchor>(link, "Яна"));
    pairName->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/pair"));
    pairName->setStyleClass("pairName");

    pairAvatar = pairAvatarWidgetSecond->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("../css/pair3.jpg")));
    pairAvatar->setStyleClass("pairAvatar");

    auto infoProfile = mainPageRight->addWidget(std::make_unique<Wt::WContainerWidget>());
    start = infoProfile->addWidget(std::make_unique<Wt::WPushButton>("Найти свою пару!"));
    start->setStyleClass("info");

    start->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/start"));

    wStackedWidget = new Wt::WStackedWidget();
    addWidget(std::unique_ptr<Wt::WStackedWidget>(wStackedWidget));

    app->internalPathChanged().connect([=] {
        handleInternalPath(app, mainPageRight);
    }
    );
}

void MainPageWidget::handleInternalPath(TinderApplication* app, Wt::WContainerWidget* mainPageRight) {
    if (app->internalPath() == "/profile") {
        showInfoProfile(mainPageRight);
    } else if (app->internalPath() == "/start") {
        showSearchPhoto(mainPageRight);
    } else if (app->internalPath() == "/pair") {
        showInfoPair(mainPageRight);
    } else if (app->internalPath() == "/user") {
        showInfoUser(mainPageRight);
    } else {
        app->setInternalPath("/",  true);
    }
}

void MainPageWidget::showSearchPhoto(Wt::WContainerWidget* mainPageRight) {
    searchPageWidget = wStackedWidget->addWidget(std::make_unique<SearchPageWidget>(mainPageRight));

    wStackedWidget->setCurrentWidget(searchPageWidget);
}
void MainPageWidget::showInfoProfile(Wt::WContainerWidget* mainPageRight) {
    profileWidget = wStackedWidget->addWidget(std::make_unique<ProfileWidget>(mainPageRight));

    wStackedWidget->setCurrentWidget(profileWidget);
}

void MainPageWidget::showInfoPair(Wt::WContainerWidget* mainPageRight) {
    pairWidget = wStackedWidget->addWidget(std::make_unique<PairWidget>(mainPageRight));

    wStackedWidget->setCurrentWidget(pairWidget);
}

void MainPageWidget::showInfoUser(Wt::WContainerWidget* mainPageRight) {
    userWidget = wStackedWidget->addWidget(std::make_unique<UserWidget>(mainPageRight));

    wStackedWidget->setCurrentWidget(userWidget);
}
