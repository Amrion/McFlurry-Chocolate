#pragma once
#include <Wt/WApplication.h>
#include <Wt/WServer.h>

#include "../server_temp/TinderServer.h"

class TinderApplication : public Wt::WApplication
{
public:
    TinderApplication(const Wt::WEnvironment&, TinderServer&);

private:
    TinderServer& server;
    const Wt::WEnvironment& env;
};
