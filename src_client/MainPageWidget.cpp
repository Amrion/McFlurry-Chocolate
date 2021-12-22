#include "MainPageWidget.h"

MainPageWidget::MainPageWidget(User &user, TinderServer &server, TinderApplication *app, TinderWidget *menu)
        : user(user), server(server) {
    creatPage(app, menu);
}

void MainPageWidget::creatPage(TinderApplication *app, TinderWidget *menu) {
    clear();
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


    mainPageRight = mainPage->addWidget(std::make_unique<Wt::WContainerWidget>());
    mainPageRight->setStyleClass("people");

    exit = myNameWidget->addWidget(std::make_unique<Wt::WPushButton>("Выйти"));
    exit->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/"));
    exit->setStyleClass("exit");

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

        do {
            pairsInfo[j] = server.db_.user_info(pairsLogin[j]);
            std::vector<std::string> photoes = server.db_.user_image(pairsInfo[j].user_id);
            link = Wt::WLink("/pair/" + std::to_string(pairsInfo[j].user_id));
            pairName = pairAvatarWidget->addWidget(std::make_unique<Wt::WAnchor>(link, pairsInfo[j].name));
            pairName->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/pair/" + std::to_string(pairsInfo[j].user_id)));
            pairName->setStyleClass("pairName");

            if (pairsInfo[j].deleted) {
                pairAvatar = pairAvatarWidget->addWidget(std::make_unique<Wt::WImage>("../css/delete.jpeg"));
                pairAvatar->setStyleClass("pairAvatar");
            } else {
                pairAvatar = pairAvatarWidget->addWidget(std::make_unique<Wt::WImage>(Wt::WLink(photoes[0])));
                pairAvatar->setStyleClass("pairAvatar");
            }

            ++j;
        } while (j % 2 != 0 && j != pairsLogin.size());
    }



    auto infoProfile = mainPageRight->addWidget(std::make_unique<Wt::WContainerWidget>());
    start = infoProfile->addWidget(std::make_unique<Wt::WPushButton>("Найти свою пару!"));
    start->setStyleClass("info");

    start->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/start"));

    wStackedWidget = new Wt::WStackedWidget();
    addWidget(std::unique_ptr<Wt::WStackedWidget>(wStackedWidget));

    app->internalPathChanged().connect([=] {
                                           handleInternalPath(menu, app);
                                       }
    );
}

void MainPageWidget::handleInternalPath(TinderWidget *menu, TinderApplication *app) {
    if (app->internalPath() == "/start") {
        showSearchPhoto(app);
    }
    for (size_t i = 0; i < pairsLogin.size(); ++i) {
        if (app->internalPath() == "/pair/" + std::to_string(pairsInfo[i].user_id)) {
            showInfoPair(pairsInfo[i]);
            break;
        }
    }
    if (app->internalPath() == "/user") {
        showInfoUser(app);
    }
    if (app->internalPath() == "/") {
        showLoginPage(menu, app);
    }
}

void MainPageWidget::showSearchPhoto( TinderApplication *app) {
    searchPageWidget = wStackedWidget->addWidget(std::make_unique<SearchPageWidget>(mainPageRight, user, server, app));

    wStackedWidget->setCurrentWidget(searchPageWidget);
}

void MainPageWidget::showInfoPair(const USERS_INFO &pairInfo) {
    pairWidget = wStackedWidget->addWidget(std::make_unique<PairWidget>(mainPageRight, pairInfo, server, user));

    wStackedWidget->setCurrentWidget(pairWidget);
}

void MainPageWidget::showInfoUser(TinderApplication* app) {
    userWidget = wStackedWidget->addWidget(std::make_unique<UserWidget>(mainPageRight, user, server, app));

    wStackedWidget->setCurrentWidget(userWidget);
}

void MainPageWidget::showLoginPage(TinderWidget *menu, TinderApplication *app) {
    if (user.deleted) {
        int id = server.db_.user_id(user.username);
        while (!user.user_image.empty()) {
            server.db_.delete_image(id, "");
            user.user_image.pop_back();
        }

        USERS_INFO usersInfo;
        usersInfo.user_id = id;
        usersInfo.name = user.name;
        usersInfo.deleted = true;
        //ls | grep -P "^A.*[0-9]{2}$" | xargs -d"\n" rm
        std::string deletePhotos = "rm ../users_images/profilePhoto" + std::to_string(id) + "*";
        system(deletePhotos.c_str());
        server.db_.save_user(usersInfo);
    }
    menu->logout();
    menu = wStackedWidget->addWidget(std::make_unique<TinderWidget>(server, app));

    Wt::WWebWidget::doJavaScript("location.reload()");
    wStackedWidget->setCurrentWidget(menu);
}
