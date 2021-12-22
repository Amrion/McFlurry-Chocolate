#include "PairWidget.h"

PairWidget::PairWidget(Wt::WContainerWidget* mainPageRight, const USERS_INFO& pairInfo, TinderServer& server, User& user) : server(server), user(user) {
    createInfoPage(mainPageRight, pairInfo);
}

void PairWidget::createInfoPage(Wt::WContainerWidget* mainPageRight, const USERS_INFO& pairInfo) {
    mainPageRight->clear();

    auto info = mainPageRight->addWidget(std::make_unique<Wt::WContainerWidget>());
    info->setStyleClass("profileInfo");

    std::vector<std::string> photoes = server.db_.user_image(pairInfo.user_id);

    if (pairInfo.deleted) {
        photo = info->addWidget(std::make_unique<Wt::WImage>("../css/delete.jpeg"));
        photo->setStyleClass("photoProfile");
    } else {
        photo = info->addWidget(std::make_unique<Wt::WImage>(Wt::WLink(photoes[0])));
        photo->setStyleClass("photoProfile");
    }

    name = info->addWidget(std::make_unique<Wt::WText>(pairInfo.name));
    name->setStyleClass("nameProfile");

    if (pairInfo.deleted) {
        auto deleteP = info->addWidget(std::make_unique<Wt::WText>());
        deleteP->setText("Аккаунт удален!");
        deleteP->setStyleClass("deleteP");
    }

    if (!pairInfo.deleted) {
        sex = info->addWidget(std::make_unique<Wt::WText>(pairInfo.gender));
        sex->setStyleClass("otherAge");

        age = info->addWidget(std::make_unique<Wt::WText>(std::to_string(pairInfo.age)));
        age->setStyleClass("otherAge");

        fac = info->addWidget(std::make_unique<Wt::WText>(pairInfo.faculty + " - " + std::to_string(pairInfo.course_number) + " Курс"));
        fac->setStyleClass("otherAge");

        discr = info->addWidget(std::make_unique<Wt::WText>(pairInfo.description));
        discr->setStyleClass("otherDiscr");

        Wt::WLink link = Wt::WLink(pairInfo.vk_link);
        link.setTarget(Wt::LinkTarget::NewWindow);
        net = info->addWidget(std::make_unique<Wt::WAnchor>(link, pairInfo.vk_link));
        net->setStyleClass("vkNet");

        link = Wt::WLink(pairInfo.telegram_link);
        link.setTarget(Wt::LinkTarget::NewWindow);
        tg = info->addWidget(std::make_unique<Wt::WAnchor>(link, pairInfo.telegram_link));
        tg->setStyleClass("vkNet");
    }

    back = mainPageRight->addWidget(std::make_unique<Wt::WPushButton>("На страницу поиска"));
    back->setStyleClass("info");
    user.rec_users = server.db_.user_rec(user.username);
    back->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/start"));
}