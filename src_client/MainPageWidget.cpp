#include "MainPageWidget.h"


MainPageWidget::MainPageWidget(User& user, TinderServer& server, TinderApplication* app)
    : user(user), server(server) {
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
    userName = myNameWidget->addWidget(std::make_unique<Wt::WAnchor>(link, "Даниил"));
    userName->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/user"));
    userName->setStyleClass("name");

    exit = myNameWidget->addWidget(std::make_unique<Wt::WPushButton>("Выйти"));
    exit->setStyleClass("exit");
    exit->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/"));

    auto pWidget = mainPageLeft->addWidget(std::make_unique<Wt::WContainerWidget>());
    pWidget->setStyleClass("pair");
    pair = pWidget->addWidget(std::make_unique<Wt::WText>("Пары"));
    pair->setStyleClass("pairText");

    int j = 0;
    std::vector<std::string> pairsLogin = server.db_.pairs_login(user.username);
    std::vector<USERS_INFO> pairsInfo(user.num_pairs);
    while (j < user.num_pairs) {
        auto pairAvatarWidget = mainPageLeft->addWidget(std::make_unique<Wt::WContainerWidget>());
        pairAvatarWidget->setStyleClass("pairDiv");

        do  {
            pairsInfo[j] = server.db_.user_info(pairsLogin[j]);
            link = Wt::WLink("/pair/" + pairsInfo[j].name);
            pairName = pairAvatarWidget->addWidget(std::make_unique<Wt::WAnchor>(link, pairsInfo[j].name));
            pairName->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/pair/" + pairsInfo[j].name));
            pairName->setStyleClass("pairName");

            pairAvatar = pairAvatarWidget->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("../css/pair" + std::to_string(j + 1) + ".jpg")));
            pairAvatar->setStyleClass("pairAvatar");
            ++j;
        } while (j % 2 != 0 && j != user.num_pairs);
    }

    auto infoProfile = mainPageRight->addWidget(std::make_unique<Wt::WContainerWidget>());
    start = infoProfile->addWidget(std::make_unique<Wt::WPushButton>("Найти свою пару!"));
    start->setStyleClass("info");

    start->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/start"));

    wStackedWidget = new Wt::WStackedWidget();
    addWidget(std::unique_ptr<Wt::WStackedWidget>(wStackedWidget));

    app->internalPathChanged().connect([=] {
        handleInternalPath(app, mainPageRight, pairsInfo);
    }
    );
}

void MainPageWidget::handleInternalPath(TinderApplication* app, Wt::WContainerWidget* mainPageRight,
                                        std::vector<USERS_INFO> pairsInfo) {
    auto iter = user.rec_users.begin();
    while (iter != user.rec_users.end()) {
        if (app->internalPath() == "/profile") {
            showInfoProfile(mainPageRight, *iter);
            break;
        }
        iter++;
    }
    if (app->internalPath() == "/start") {
        showSearchPhoto(mainPageRight);
    }
    for (int i = 0; i < user.num_pairs; ++i) {
        if (app->internalPath() == "/pair/" + pairsInfo[i].name) {
            showInfoPair(mainPageRight, pairsInfo[i]);
            break;
        }
    }
    if (app->internalPath() == "/user") {
        showInfoUser(mainPageRight);
    } else {
        app->setInternalPath("/",  true);
    }
}

void MainPageWidget::showSearchPhoto(Wt::WContainerWidget* mainPageRight) {
    searchPageWidget = wStackedWidget->addWidget(std::make_unique<SearchPageWidget>(mainPageRight, user, server.db_));

    wStackedWidget->setCurrentWidget(searchPageWidget);
}
void MainPageWidget::showInfoProfile(Wt::WContainerWidget* mainPageRight, const std::string& profile) {
    profileWidget = wStackedWidget->addWidget(std::make_unique<ProfileWidget>(mainPageRight, profile, server.db_));

    wStackedWidget->setCurrentWidget(profileWidget);
}

void MainPageWidget::showInfoPair(Wt::WContainerWidget* mainPageRight, const USERS_INFO& pairInfo) {
    pairWidget = wStackedWidget->addWidget(std::make_unique<PairWidget>(mainPageRight, pairInfo));

    wStackedWidget->setCurrentWidget(pairWidget);
}

void MainPageWidget::showInfoUser(Wt::WContainerWidget* mainPageRight) {
    userWidget = wStackedWidget->addWidget(std::make_unique<UserWidget>(mainPageRight, user, server.db_));

    wStackedWidget->setCurrentWidget(userWidget);
}
