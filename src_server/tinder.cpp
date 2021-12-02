#include <Wt/WApplication.h>
#include <Wt/WServer.h>

#include "TinderApp.h"
#include "Session.h"

using namespace Wt;

std::unique_ptr<WApplication> createApplication(const WEnvironment& env)
{
    auto app = std::make_unique<WApplication>(env);

    app->setTitle("BMSTU Tinder");

    app->root()->addWidget(std::make_unique<TinderApp>());

    return app;
}


int main(int argc, char **argv)
{
    try {
        WServer server(argc, argv, WTHTTP_CONFIGURATION);

        server.addEntryPoint(EntryPointType::Application, createApplication);

        server.run();
    } catch (WServer::Exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }
}