#include <Wt/WServer.h>

#include "TinderServer.hpp"


TinderServer::TinderServer(Wt::WServer &server, const Postgre_DB &db)
        : server_(server), db_(db) {
}

bool TinderServer::signUp(User &user) {
    return false;
}

bool TinderServer::login(User &user) {
    return false;
}

void TinderServer::logout(const User &user) {

}
