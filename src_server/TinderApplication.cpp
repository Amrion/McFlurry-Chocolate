#include "TinderApplication.hpp"

TinderApplication::TinderApplication(const Wt::WEnvironment& env,
                                 TinderServer& server)
        : WApplication(env),
          server_(server),
          env_(env) {
    setTitle("BMSTU Tinder");
    useStyleSheet("../css/tinder.css");

    TinderWidget *tinderWidget =
            root()->addWidget(std::make_unique<TinderWidget>(server_));
    tinderWidget->setStyleClass("Tinder");
}
