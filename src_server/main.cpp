#include "TinderApplication.hpp"
#include "UpdateRec.h"

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment &env, TinderServer &server) {
    return std::make_unique<TinderApplication>(env, server);
}

int main(int argc, char *argv[]) {
    Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);
    Postgre_DB db("127.0.0.1", "5432", "bauman_tinder", "server", "server_password");

    TinderServer tinderServer(server, db);

    server.addEntryPoint(Wt::EntryPointType::Application,
                         std::bind(createApplication, std::placeholders::_1,
                                   std::ref(tinderServer)));

   UpdateManager updateManager(db);

    if (server.start()) {
        auto t = updateManager.start();
        int sig = Wt::WServer::waitForShutdown();
        std::cerr << "Shutting down: (signal = " << sig << ")" << std::endl;
        server.stop();
    }

    return 0;
}
