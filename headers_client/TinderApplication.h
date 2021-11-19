#pragma once

class TinderApplication : public Wt::WApplication
{
public:
    TinderApplication(const Wt::WEnvironment& env);

private:
    const Wt::WEnvironment&       env_;
