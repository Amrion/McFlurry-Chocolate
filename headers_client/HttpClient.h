#pragma once

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WStringStream.h>
#include <Wt/WText.h>
#include <Wt/Http/Client.h>
#include <Wt/Http/Message.h>

class HttpClient : public Wt::WApplication {
public:
    HttpClient(const Wt::WEnvironment &env);

private:
    void doRequest();
    void requestDone(Wt::AsioWrapper::error_code ec, const Wt::Http::Message &msg);

    Wt::WContainerWidget* requestForm_;
    Wt::WText* result_;
    Wt::Http::Client client_;
    Wt::WStringStream answer;
};

