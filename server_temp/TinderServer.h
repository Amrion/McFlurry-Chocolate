#pragma once
#include <Wt/WServer.h>

class TinderServer {
public:
    TinderServer(Wt::WServer &server);

private:
    Wt::WServer& server;
};