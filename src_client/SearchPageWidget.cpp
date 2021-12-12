#include "SearchPageWidget.h"


SearchPageWidget::SearchPageWidget(Wt::WContainerWidget* mainPageRight, User& user, TinderServer& server) : user(user),
    server(server),
    number(0),
    kol(0) {
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

    USERS_INFO profile = server.db_.user_info(user.rec_users[kol]);
    photoes = server.db_.user_image(server.db_.user_id(user.rec_users[kol]));


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
        forward->clicked().connect([=] {
            changePhotoBack(mainPhoto);
        });
        back->clicked().connect([=] {
            changePhotoForward(mainPhoto);
        });
    }

    auto infoProfile = mainPageRight->addWidget(std::make_unique<Wt::WContainerWidget>());
    info = infoProfile->addWidget(std::make_unique<Wt::WPushButton>("Посмотреть профиль"));
    info->setStyleClass("info");

    dislike->clicked().connect([=] {
        changeMan(mainPhoto, mainPageRight);

    });
    like->clicked().connect([=] {
        changeMan(mainPhoto, mainPageRight);

    });

    info->clicked().connect([=] {
            showInfoProfile(mainPageRight);
    });
}

void SearchPageWidget::showInfoProfile(Wt::WContainerWidget* mainPageRight) {
    mainPageRight->clear();


    USERS_INFO profile = server.db_.user_info(user.rec_users[kol]);

    auto infoPage = mainPageRight->addWidget(std::make_unique<Wt::WContainerWidget>());
    infoPage->setStyleClass("profileInfo");

    photoProf = infoPage->addWidget(std::make_unique<Wt::WImage>(Wt::WLink(photoes[0])));
    photoProf->setStyleClass("photoProfile");

    name = infoPage->addWidget(std::make_unique<Wt::WText>(profile.name));
    name->setStyleClass("nameProfile");

    sex = infoPage->addWidget(std::make_unique<Wt::WText>(profile.gender));
    sex->setStyleClass("otherAge");

    age = infoPage->addWidget(std::make_unique<Wt::WText>(std::to_string(profile.age)));
    age->setStyleClass("otherAge");

    fac = infoPage->addWidget(std::make_unique<Wt::WText>(profile.faculty + " - " + std::to_string(profile.course_number) + " Курс"));
    fac->setStyleClass("otherAge");

    discr = infoPage->addWidget(std::make_unique<Wt::WText>(profile.description));
    discr->setStyleClass("otherDiscr");

    backSearch = mainPageRight->addWidget(std::make_unique<Wt::WPushButton>("Вернуться к поиску"));
    backSearch->setStyleClass("info");
    backSearch->clicked().connect([=] {
        createSearchPage(mainPageRight);
    });
}

void SearchPageWidget::changeMan(Wt::WContainerWidget* contPhoto, Wt::WContainerWidget* mainPageRight) {
    contPhoto->removeWidget(photo);
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
        photoes = server.db_.user_image(server.db_.user_id(user.rec_users[kol]));
        photo = contPhoto->addWidget(std::make_unique<Wt::WImage>(Wt::WLink(photoes[0])));
        photo->setStyleClass("photo");
        number = 0;
        createSearchPage(mainPageRight);
    }
}

void SearchPageWidget::changePhotoForward(Wt::WContainerWidget* contPhoto) {
    contPhoto->removeWidget(photo);

    if (number != photoes.size() - 1) {
        number++;
    } else {
        number = 0;
    }
    photo = contPhoto->addWidget(std::make_unique<Wt::WImage>(Wt::WLink(photoes[number])));
    photo->setStyleClass("photo");
}

void SearchPageWidget::changePhotoBack(Wt::WContainerWidget* contPhoto) {
    contPhoto->removeWidget(photo);

    if (number != photoes.size() - photoes.size()) {
        number--;
    } else {
        number = photoes.size() - 1;
    }
    photo = contPhoto->addWidget(std::make_unique<Wt::WImage>(Wt::WLink(photoes[number])));
    photo->setStyleClass("photo");
}

