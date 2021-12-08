#pragma once
#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <Wt/WServer.h>
#include <Wt/WTimer.h>

#include "TinderServer.hpp"


class TinderApplication : public Wt::WApplication {
public:
    TinderApplication(const Wt::WEnvironment &env, TinderServer &server);

private:
    TinderServer                  &server_;
    const Wt::WEnvironment      &env_;
    std::unique_ptr<Wt::WTimer>  timer_;
};
