#include "PairWidget.h"

PairWidget::PairWidget(Wt::WContainerWidget* mainPageRight) {
    createInfoPage(mainPageRight);
}

void PairWidget::createInfoPage(Wt::WContainerWidget* mainPageRight) {
    mainPageRight->clear();

    auto info = mainPageRight->addWidget(std::make_unique<Wt::WContainerWidget>());
    info->setStyleClass("profileInfo");

    photo = info->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("../css/pair1.jpg")));
    photo->setStyleClass("photoProfile");

    name = info->addWidget(std::make_unique<Wt::WText>("Оля"));
    name->setStyleClass("nameProfile");

    age = info->addWidget(std::make_unique<Wt::WText>("20"));
    age->setStyleClass("otherAge");
    discr = info->addWidget(std::make_unique<Wt::WText>("Короче, люблю все. Люблю Скрипа, люблю гулять и тусить"));
    discr->setStyleClass("otherDiscr");

    Wt::WLink link = Wt::WLink("https://vk.com/id71276649");
    link.setTarget(Wt::LinkTarget::NewWindow);
    net = info->addWidget(std::make_unique<Wt::WAnchor>(link, "https://vk.com/id71276649"));
    net->setStyleClass("vkNet");

    back = mainPageRight->addWidget(std::make_unique<Wt::WPushButton>("На страницу поиска"));
    back->setStyleClass("info");
    back->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/start"));
}