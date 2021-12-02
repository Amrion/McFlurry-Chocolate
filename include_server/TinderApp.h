#ifndef MCFLURRY_CHOCOLATE_TINDERAPP_H
#define MCFLURRY_CHOCOLATE_TINDERAPP_H

#include <Wt/WContainerWidget.h>

#include "Session.h"

using namespace Wt;

namespace Wt {
    class WStackedWidget;
    class WAnchor;
}

class TinderWidget;
class Session;

class TinderApp : public WContainerWidget
{
public:
    TinderApp();

    void handleInternalPath(const std::string &internalPath);

private:
    WStackedWidget    *mainStack_;
    TinderWidget     *mainPage;
    WContainerWidget  *links_;
    WAnchor           *backToAppAnchor_;
    WAnchor           *settingsAnchor_;

    Session session_;

    void onAuthEvent();
    void showMainPage();
    void showSettings();
};

#endif //MCFLURRY_CHOCOLATE_TINDERAPP_H
