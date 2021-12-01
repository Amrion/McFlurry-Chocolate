#include "SearchPageWidget.h"


SearchPageWidget::SearchPageWidget(Wt::WContainerWidget* mainPageRight) {
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

    info->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/profile"));
}

void SearchPageWidget::changePhoto(Wt::WContainerWidget* contPhoto) {
    contPhoto->removeWidget(photo);
    photo = contPhoto->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("../css/main.jpg")));
    photo->setStyleClass("photo");
}

void SearchPageWidget::changePhototemp(Wt::WContainerWidget* contPhoto) {
    contPhoto->removeWidget(photo);
    photo = contPhoto->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("../css/Liza1.jpg")));
    photo->setStyleClass("photo");
}