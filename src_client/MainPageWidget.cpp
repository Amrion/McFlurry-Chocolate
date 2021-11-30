#include "MainPageWidget.h"

MainPageWidget::MainPageWidget(std::map<std::string, std::string> data, TinderServer& server)
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

    Wt::WLink link = Wt::WLink("https://vk.com/dtarnovsky");
    link.setTarget(Wt::LinkTarget::NewWindow);
    name = myNameWidget->addWidget(std::make_unique<Wt::WAnchor>(link, "Даниил"));
    name->setStyleClass("name");

    auto pairWidget = mainPageLeft->addWidget(std::make_unique<Wt::WContainerWidget>());
    pairWidget->setStyleClass("pair");
    pair = pairWidget->addWidget(std::make_unique<Wt::WText>("Пары"));
    pair->setStyleClass("pairText");

    auto pairAvatarWidgetFirst = mainPageLeft->addWidget(std::make_unique<Wt::WContainerWidget>());
    pairAvatarWidgetFirst->setStyleClass("pairDiv");

    link = Wt::WLink("https://vk.com/id71276649");
    link.setTarget(Wt::LinkTarget::NewWindow);
    pairName = pairAvatarWidgetFirst->addWidget(std::make_unique<Wt::WAnchor>(link, "Оля"));
    pairName->setStyleClass("pairName");
    pairAvatar = pairAvatarWidgetFirst->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("../css/pair1.jpg")));
    pairAvatar->setStyleClass("pairAvatar");

    link = Wt::WLink("https://vk.com/rybinaarina");
    link.setTarget(Wt::LinkTarget::NewWindow);
    pairName = pairAvatarWidgetFirst->addWidget(std::make_unique<Wt::WAnchor>(link, "Арина"));
    pairName->setStyleClass("pairName");
    pairAvatar = pairAvatarWidgetFirst->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("../css/pair2.jpg")));
    pairAvatar->setStyleClass("pairAvatar");

    auto pairAvatarWidgetSecond = mainPageLeft->addWidget(std::make_unique<Wt::WContainerWidget>());
    pairAvatarWidgetSecond->setStyleClass("pairDiv");

    link = Wt::WLink("https://vk.com/yana_kotukova");
    link.setTarget(Wt::LinkTarget::NewWindow);
    pairName = pairAvatarWidgetSecond->addWidget(std::make_unique<Wt::WAnchor>(link, "Яна"));
    pairName->setStyleClass("pairName");
    pairAvatar = pairAvatarWidgetSecond->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("../css/pair3.jpg")));
    pairAvatar->setStyleClass("pairAvatar");


    auto photos = mainPageRight->addWidget(std::make_unique<Wt::WContainerWidget>());
    photos->addStyleClass("photos");

    auto buttonsLeft = photos->addWidget(std::make_unique<Wt::WContainerWidget>());
    buttonsLeft->setStyleClass("butLeft");

    back = buttonsLeft->addWidget(std::make_unique<Wt::WPushButton>(""));
    back->setStyleClass("back");

    dislike = buttonsLeft->addWidget(std::make_unique<Wt::WPushButton>(""));
    dislike->setStyleClass("dislike");

    auto mainPhoto = photos->addWidget(std::make_unique<Wt::WContainerWidget>());
    photo = mainPhoto->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("../css/Liza1.jpg")));
    photo->setStyleClass("photo");

    auto buttonsRight = photos->addWidget(std::make_unique<Wt::WContainerWidget>());
    buttonsRight->setStyleClass("butRight");

    forward = buttonsRight->addWidget(std::make_unique<Wt::WPushButton>(""));
    forward->setStyleClass("forward");

    like = buttonsRight->addWidget(std::make_unique<Wt::WPushButton>(""));
    like->setStyleClass("like");

    dislike->clicked().connect([=] {
        changePhoto(mainPhoto);
    });
    like->clicked().connect([=] {
        changePhototemp(mainPhoto);
    });

    auto infoProfile = mainPageRight->addWidget(std::make_unique<Wt::WContainerWidget>());
    info = infoProfile->addWidget(std::make_unique<Wt::WPushButton>("Посмотреть профиль"));
    info->setStyleClass("info");
}

void MainPageWidget::changePhoto(Wt::WContainerWidget* contPhoto) {
    contPhoto->removeWidget(photo);
    photo = contPhoto->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("../css/main.jpg")));
    photo->setStyleClass("photo");
}

void MainPageWidget::changePhototemp(Wt::WContainerWidget* contPhoto) {
    contPhoto->removeWidget(photo);
    photo = contPhoto->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("../css/Liza1.jpg")));
    photo->setStyleClass("photo");
}