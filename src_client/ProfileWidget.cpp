#include "ProfileWidget.h"

#include <utility>

ProfileWidget::ProfileWidget(Wt::WContainerWidget* mainPageRight, std::string login, TinderServer& server) : server(server) {
    createInfoPage(mainPageRight, std::move(login));
}

void ProfileWidget::createInfoPage(Wt::WContainerWidget* mainPageRight, std::string login) {
    mainPageRight->clear();


}

