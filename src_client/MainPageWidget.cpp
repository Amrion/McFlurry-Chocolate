#include "MainPageWidget.h"

MainPageWidget::MainPageWidget(User& user, TinderServer& server, TinderApplication* app, TinderWidget* menu)
    : user(user), server(server) {
    auto mainPage = addWidget(std::make_unique<Wt::WContainerWidget>());
    mainPage->setStyleClass("page");

    auto mainPageLeft = mainPage->addWidget(std::make_unique<Wt::WContainerWidget>());
    mainPageLeft->setStyleClass("me");

    auto myNameWidget = mainPageLeft->addWidget(std::make_unique<Wt::WContainerWidget>());
    myNameWidget->setStyleClass("myName");

    avatar = myNameWidget->addWidget(std::make_unique<Wt::WImage>(Wt::WLink(user.user_image[0])));
    avatar->setStyleClass("avatar");

    Wt::WLink link = Wt::WLink("/user");
    userName = myNameWidget->addWidget(std::make_unique<Wt::WAnchor>(link, user.name));
    userName->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/user"));
    userName->setStyleClass("name");

    exit = myNameWidget->addWidget(std::make_unique<Wt::WPushButton>("Выйти"));
    exit->setStyleClass("exit");
    exit->clicked().connect([=]{
        showLoginPage(menu);
    });

    auto pWidget = mainPageLeft->addWidget(std::make_unique<Wt::WContainerWidget>());
    pWidget->setStyleClass("pair");
    pair = pWidget->addWidget(std::make_unique<Wt::WText>("Пары"));
    pair->setStyleClass("pairText");

    size_t j = 0;
    pairsLogin = server.db_.pairs_login(user.username);
    pairsInfo.resize(pairsLogin.size());

    while (j < pairsLogin.size()) {
        auto pairAvatarWidget = mainPageLeft->addWidget(std::make_unique<Wt::WContainerWidget>());
        pairAvatarWidget->setStyleClass("pairDiv");

        do  {
            pairsInfo[j] = server.db_.user_info(pairsLogin[j]);
            std::vector<std::string> photoes = server.db_.user_image(pairsInfo[j].user_id);
            link = Wt::WLink("/pair/" + pairsInfo[j].name);
            pairName = pairAvatarWidget->addWidget(std::make_unique<Wt::WAnchor>(link, pairsInfo[j].name));
            pairName->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/pair/" + pairsInfo[j].name));
            pairName->setStyleClass("pairName");

            pairAvatar = pairAvatarWidget->addWidget(std::make_unique<Wt::WImage>(Wt::WLink(photoes[0])));
            pairAvatar->setStyleClass("pairAvatar");
            ++j;
        } while (j % 2 != 0 && j != pairsLogin.size());
    }

    auto mainPageRight = mainPage->addWidget(std::make_unique<Wt::WContainerWidget>());
    mainPageRight->setStyleClass("people");

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
    if (app->internalPath() == "/start") {
        showSearchPhoto(mainPageRight, app);
    }
    for (size_t i = 0; i < pairsLogin.size(); ++i) {
        if (app->internalPath() == "/pair/" + pairsInfo[i].name) {
            showInfoPair(mainPageRight, pairsInfo[i]);
            break;
        }
    }
    if (app->internalPath() == "/user") {
        showInfoUser(mainPageRight);
    }
}

void MainPageWidget::showSearchPhoto(Wt::WContainerWidget* mainPageRight, TinderApplication* app) {
    searchPageWidget = wStackedWidget->addWidget(std::make_unique<SearchPageWidget>(mainPageRight, user, server, app));

    wStackedWidget->setCurrentWidget(searchPageWidget);
}

void MainPageWidget::showInfoPair(Wt::WContainerWidget* mainPageRight, const USERS_INFO& pairInfo) {
    pairWidget = wStackedWidget->addWidget(std::make_unique<PairWidget>(mainPageRight, pairInfo, server));

    wStackedWidget->setCurrentWidget(pairWidget);
}

void MainPageWidget::showInfoUser(Wt::WContainerWidget* mainPageRight) {
    userWidget = wStackedWidget->addWidget(std::make_unique<UserWidget>(mainPageRight, user, server));

    wStackedWidget->setCurrentWidget(userWidget);
}

void MainPageWidget::showLoginPage(TinderWidget* menu) {
    menu->logout();
}
