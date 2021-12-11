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

    size_t kol = 0;
    USERS_INFO profile = server.db_.user_info(user.rec_users[kol]);
    std::vector<std::string> photoes = server.db_.user_image(server.db_.user_id(user.rec_users[kol]));
    size_t number = 0;


    auto mainPhoto = photos->addWidget(std::make_unique<Wt::WContainerWidget>());
    photo = mainPhoto->addWidget(std::make_unique<Wt::WImage>(Wt::WLink(photoes[number])));
    photo->setStyleClass("photo");

    auto buttonsRight = photos->addWidget(std::make_unique<Wt::WContainerWidget>());
    buttonsRight->setStyleClass("butRight");

    forward = buttonsRight->addWidget(std::make_unique<Wt::WPushButton>(""));
    forward->setStyleClass("forward");

    like = buttonsRight->addWidget(std::make_unique<Wt::WPushButton>(""));
    like->setStyleClass("like");

    USERS_INFO profileInfo = server.db_.user_info(user.rec_users[kol]);
    if (number != photoes.size() - 1) {
        forward->clicked().connect([=, &number] {
            changePhotoBack(mainPhoto, photoes, number);
        });
        back->clicked().connect([=, &number] {
            changePhotoForward(mainPhoto, photoes, number);
        });
    }

    auto infoProfile = mainPageRight->addWidget(std::make_unique<Wt::WContainerWidget>());
    info = infoProfile->addWidget(std::make_unique<Wt::WPushButton>("Посмотреть профиль"));
    info->setStyleClass("info");

    dislike->clicked().connect([=, &kol] {
        changeMan(mainPhoto, user.rec_users, kol);

    });
    like->clicked().connect([=, &kol] {
        changeMan(mainPhoto, user.rec_users, kol);

    });


    info->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/profile"));
}

void SearchPageWidget::changeMan(Wt::WContainerWidget* contPhoto,
                                 std::vector<std::string> man, size_t& kol) {
    contPhoto->removeWidget(photo);
    if (kol > 1000000000) {
        kol = 0;
    }
    kol++;
    if (kol == user.rec_users.size()) {
        Wt::WText* error = contPhoto->addWidget(std::make_unique<Wt::WText>("Больше никого нет. Приходи завтра"));
        error->setStyleClass("errorPhoto");
        info->hide();
        dislike->hide();
        like->hide();
        forward->hide();
        back->hide();
    } else {
        USERS_INFO profile = server.db_.user_info(man[kol]);
        std::vector<std::string> avatar = server.db_.user_image(server.db_.user_id(man[kol]));
        photo = contPhoto->addWidget(std::make_unique<Wt::WImage>(Wt::WLink(avatar[0])));
        photo->setStyleClass("photo");
    }
}

void SearchPageWidget::changePhotoForward(Wt::WContainerWidget* contPhoto, std::vector<std::string> photoes, size_t& number) {
    contPhoto->removeWidget(photo);

    if (number != photoes.size() - 1) {
        number++;
    } else {
        number = 0;
    }
    photo = contPhoto->addWidget(std::make_unique<Wt::WImage>(Wt::WLink(photoes[number])));
    photo->setStyleClass("photo");
}

void SearchPageWidget::changePhotoBack(Wt::WContainerWidget* contPhoto, std::vector<std::string> photoes, size_t& number) {
    contPhoto->removeWidget(photo);

    if (number != photoes.size() - photoes.size()) {
        number--;
    } else {
        number = photoes.size() - 1;
    }
    photo = contPhoto->addWidget(std::make_unique<Wt::WImage>(Wt::WLink(photoes[number])));
    photo->setStyleClass("photo");
}

