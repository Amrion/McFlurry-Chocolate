#include "SearchPageWidget.h"


SearchPageWidget::SearchPageWidget(Wt::WContainerWidget* mainPageRight, User& user, TinderServer& server) : user(user), server(server) {
    createSearchPage(mainPageRight);
}

void SearchPageWidget::createSearchPage(Wt::WContainerWidget* mainPageRight) {
    mainPageRight->clear();

    auto photos = mainPageRight->addWidget(std::make_unique<Wt::WContainerWidget>());
    photos->addStyleClass("photos");

    auto buttonsLeft = photos->addWidget(std::make_unique<Wt::WContainerWidget>());
    buttonsLeft->setStyleClass("butLeft");

    back = buttonsLeft->addWidget(std::make_unique<Wt::WPushButton>(""));
    back->setStyleClass("back");

    dislike = buttonsLeft->addWidget(std::make_unique<Wt::WPushButton>(""));
    dislike->setStyleClass("dislike");

    auto iter = user.rec_users.begin();
    USERS_INFO profile = server.db_.user_info(*iter);

    auto mainPhoto = photos->addWidget(std::make_unique<Wt::WContainerWidget>());
    photo = mainPhoto->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("../css/Liza1.jpg")));
    photo->setStyleClass("photo");

    auto buttonsRight = photos->addWidget(std::make_unique<Wt::WContainerWidget>());
    buttonsRight->setStyleClass("butRight");

    forward = buttonsRight->addWidget(std::make_unique<Wt::WPushButton>(""));
    forward->setStyleClass("forward");

    like = buttonsRight->addWidget(std::make_unique<Wt::WPushButton>(""));
    like->setStyleClass("like");

    if (iter != user.rec_users.end()) {
        dislike->clicked().connect([&] {
            changeMan(mainPhoto, iter);
        });
        like->clicked().connect([&] {
            changeMan(mainPhoto, iter);
        });
    }

    USERS_INFO profileInfo = server.db_.user_info(*iter);
    if (profileInfo.) {
        dislike->clicked().connect([&] {
            changePhoto(mainPhoto, profileInfo);
        });
        like->clicked().connect([&] {
            changePhoto(mainPhoto, profileInfo);
        });
    }

    auto infoProfile = mainPageRight->addWidget(std::make_unique<Wt::WContainerWidget>());
    info = infoProfile->addWidget(std::make_unique<Wt::WPushButton>("Посмотреть профиль"));
    info->setStyleClass("info");

    info->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/profile"));
}

void SearchPageWidget::changeMan(Wt::WContainerWidget* contPhoto,
                                                                 std::vector<std::string>::iterator iter) {
    contPhoto->removeWidget(photo);
    iter++;
    if (iter == user.rec_users.end()) {
        Wt::WText* error = contPhoto->addWidget(std::make_unique<Wt::WText>("Больше никого нет. Приходи завтра"));
        error->setStyleClass("errorPhoto");
    } else {
        USERS_INFO profile = server.db_.user_info(*iter);
        photo = contPhoto->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("../css/main.jpg")));
        photo->setStyleClass("photo");
    }
}

void SearchPageWidget::changePhoto(Wt::WContainerWidget* contPhoto, USERS_INFO& profile) {
    contPhoto->removeWidget(photo);

    if (true) {
        photo = contPhoto->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("../css/main.jpg")));
    } else {

    }
}

