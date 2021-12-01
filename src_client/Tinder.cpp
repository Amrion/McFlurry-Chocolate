#include "TinderApplication.h"
#include "MainPageWidget.h"

TinderApplication::TinderApplication(const Wt::WEnvironment& env, TinderServer& server) : WApplication(env), server(server), env(env) {
   std::map<std::string, std::string> data;

    setTitle("BMSTU Tinder");
    useStyleSheet("../css/Tinder.css");

    MainPageWidget* mainPageWidget = root()->addWidget(std::make_unique<MainPageWidget>(data, server, this));
}

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env, TinderServer& server) {
    return std::make_unique<TinderApplication>(env, server);
}

int main(int argc, char **argv) {
    Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);
    TinderServer tinderServer(server);

    server.addEntryPoint(Wt::EntryPointType::Application, std::bind(createApplication,
                                                                    std::placeholders::_1,
                                                                    std::ref(tinderServer)));

    if (server.start()) {
        int sig = Wt::WServer::waitForShutdown();
        std::cerr << "Shutting down: (signal = " << sig << ")" << std::endl;
        server.stop();
    }
}