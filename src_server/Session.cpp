#include "Session.h"

#include "Wt/Auth/AuthService.h"
#include "Wt/Auth/HashFunction.h"
#include "Wt/Auth/PasswordService.h"
#include "Wt/Auth/PasswordStrengthValidator.h"
#include "Wt/Auth/PasswordVerifier.h"
#include "Wt/Auth/GoogleService.h"
#include "Wt/Auth/Dbo/AuthInfo.h"
#include "Wt/Auth/Dbo/UserDatabase.h"

#include <Wt/WApplication.h>
#include <Wt/WLogger.h>

#ifndef WT_WIN32

#include <unistd.h>

#endif

#if !defined(WT_WIN32) && !defined(__CYGWIN__) && !defined(ANDROID)
#define HAVE_CRYPT
#ifndef _XOPEN_CRYPT

#include <crypt.h>

#endif // _XOPEN_CRYPT
#endif

namespace dbo = Wt::Dbo;

namespace {

#ifdef HAVE_CRYPT

    class UnixCryptHashFunction : public Auth::HashFunction {
    public:
        virtual std::string compute(const std::string &msg,
                                    const std::string &salt) const {
            std::string md5Salt = "$1$" + salt;
            return crypt(msg.c_str(), md5Salt.c_str());
        }

        virtual bool verify(const std::string &msg,
                            const std::string &salt,
                            const std::string &hash) const {
            return crypt(msg.c_str(), hash.c_str()) == hash;
        }

        virtual std::string name() const {
            return "crypt";
        }
    };

#endif // HAVE_CRYPT

    class MyOAuth : public std::vector<const Auth::OAuthService *> {
    public:
        ~MyOAuth() {
            for (unsigned i = 0; i < size(); ++i)
                delete (*this)[i];
        }
    };

    Auth::AuthService myAuthService;
    Auth::PasswordService myPasswordService(myAuthService);
    MyOAuth myOAuthServices;
}

void Session::configureAuth() {
    myAuthService.setAuthTokensEnabled(true, "tindercookie");
    myAuthService.setEmailVerificationEnabled(true);

    std::unique_ptr<Auth::PasswordVerifier> verifier
            = std::make_unique<Auth::PasswordVerifier>();
    verifier->addHashFunction(std::make_unique<Auth::BCryptHashFunction>(7));

#ifdef HAVE_CRYPT
    verifier->addHashFunction(std::make_unique<UnixCryptHashFunction>());
#endif

    myPasswordService.setVerifier(std::move(verifier));
    myPasswordService.setStrengthValidator(std::make_unique<Auth::PasswordStrengthValidator>());
    myPasswordService.setAttemptThrottlingEnabled(true);

    if (Auth::GoogleService::configured())
        myOAuthServices.push_back(new Auth::GoogleService(myAuthService));
}

Session::Session() {
    auto sqlite3 = std::make_unique<Dbo::backend::Sqlite3>(WApplication::instance()->appRoot() + "auth.db");
    sqlite3->setProperty("show-queries", "true");
    session_.setConnection(std::move(sqlite3));

    session_.mapClass<User>("user");
    session_.mapClass<AuthInfo>("auth_info");
    session_.mapClass<AuthInfo::AuthIdentityType>("auth_identity");
    session_.mapClass<AuthInfo::AuthTokenType>("auth_token");

    users_ = std::make_unique<UserDatabase>(session_);

    dbo::Transaction transaction(session_);
    try {
        session_.createTables();

//        /*
//         * Add a default guest/guest account
//         */
//        Auth::User guestUser = users_->registerNew();
//        guestUser.addIdentity(Auth::Identity::LoginName, "guest");
//        myPasswordService.updatePassword(guestUser, "guest");

        log("info") << "Database created";
    } catch (...) {
        log("info") << "Using existing database";
    }

    transaction.commit();
}

Session::~Session() {
}

dbo::ptr<User> Session::user() const {
    if (login_.loggedIn()) {
        dbo::ptr<AuthInfo> authInfo = users_->find(login_.user());
        dbo::ptr<User> user = authInfo->user();

        if (!user) {
            user = session_.add(std::make_unique<User>());
            authInfo.modify()->setUser(user);
        }

        return user;
    } else
        return dbo::ptr<User>();
}

Auth::AbstractUserDatabase &Session::users() {
    return *users_;
}

const Auth::AuthService &Session::auth() {
    return myAuthService;
}

const Auth::AbstractPasswordService &Session::passwordAuth() {
    return myPasswordService;
}

const std::vector<const Auth::OAuthService *> &Session::oAuth() {
    return myOAuthServices;
}
