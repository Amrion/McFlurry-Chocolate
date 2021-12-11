#include "ProfileWidget.h"

#include <utility>

ProfileWidget::ProfileWidget(Wt::WContainerWidget* mainPageRight, std::string login, TinderServer& server) : server(server) {
    createInfoPage(mainPageRight, std::move(login));
}

void ProfileWidget::createInfoPage(Wt::WContainerWidget* mainPageRight, std::string login) {
    mainPageRight->clear();

    std::vector<std::string> photoes = server.db_.user_image(server.db_.user_id(login));
    USERS_INFO profile = server.db_.user_info(std::move(login));

    auto info = mainPageRight->addWidget(std::make_unique<Wt::WContainerWidget>());
    info->setStyleClass("profileInfo");

    photo = info->addWidget(std::make_unique<Wt::WImage>(Wt::WLink(photoes[0])));
    photo->setStyleClass("photoProfile");

    name = info->addWidget(std::make_unique<Wt::WText>(profile.name));
    name->setStyleClass("nameProfile");

    sex = info->addWidget(std::make_unique<Wt::WText>(profile.gender));
    sex->setStyleClass("otherAge");

    age = info->addWidget(std::make_unique<Wt::WText>(std::to_string(profile.age)));
    age->setStyleClass("otherAge");

    fac = info->addWidget(std::make_unique<Wt::WText>(profile.faculty + " - " + std::to_string(profile.course_number) + " Курс"));
    fac->setStyleClass("otherAge");

    discr = info->addWidget(std::make_unique<Wt::WText>(profile.description));
    discr->setStyleClass("otherDiscr");

    back = mainPageRight->addWidget(std::make_unique<Wt::WPushButton>("Вернуться к поиску"));
    back->setStyleClass("info");
    back->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/start"));
}

