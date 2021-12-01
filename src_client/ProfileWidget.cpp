#include "ProfileWidget.h"

ProfileWidget::ProfileWidget(Wt::WContainerWidget* mainPageRight) {
    createInfoPage(mainPageRight);
}

void ProfileWidget::createInfoPage(Wt::WContainerWidget* mainPageRight) {
    mainPageRight->clear();

    auto info = mainPageRight->addWidget(std::make_unique<Wt::WContainerWidget>());
    info->setStyleClass("profileInfo");

    photo = info->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("../css/Liza1.jpg")));
    photo->setStyleClass("photoProfile");

    name = info->addWidget(std::make_unique<Wt::WText>("Лиза"));
    name->setStyleClass("nameProfile");

    age = info->addWidget(std::make_unique<Wt::WText>("19"));
    age->setStyleClass("otherAge");
    discr = info->addWidget(std::make_unique<Wt::WText>("Меня зовут Лиза. Я люблю писать, читать. Хожу в Бомонку. Кушаю суши. В общем, пиши)"));
    discr->setStyleClass("otherDiscr");

    back = mainPageRight->addWidget(std::make_unique<Wt::WPushButton>("Вернуться к поиску"));
    back->setStyleClass("info");
    back->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/start"));
}

