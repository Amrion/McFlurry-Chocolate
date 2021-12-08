#ifndef PROJECT_INCLUDE_SERVER_TINDERAPPLICATION_HPP_
#define PROJECT_INCLUDE_SERVER_TINDERAPPLICATION_HPP_


#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <Wt/WServer.h>
#include <Wt/WTimer.h>

#include "TinderServer.hpp"
#include "TinderWidget.hpp"


class TinderApplication : public Wt::WApplication {
public:
    TinderApplication(const Wt::WEnvironment &env, TinderServer &server);

private:
    TinderServer                  &server_;
    const Wt::WEnvironment      &env_;
    std::unique_ptr<Wt::WTimer>  timer_;
};


#endif  // PROJECT_INCLUDE_SERVER_TINDERAPPLICATION_HPP_
