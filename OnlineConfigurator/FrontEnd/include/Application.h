#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <Wt/WApplication.h>

#include "HttpClientUser.h"

namespace Wt
{
    class WGridLayout;
}

class Application final : public Wt::WApplication, public HttpClientUser
{
public:
    Application(const Wt::WEnvironment& env);

private:
    void projectRequestDone(Wt::AsioWrapper::error_code errorCode, const Wt::Http::Message& message);

    void projectSubEntitiesRequestDone(Wt::AsioWrapper::error_code errorCode, const Wt::Http::Message& message);

private:
    Wt::WGridLayout* _gridLayout = nullptr;
};

#endif //_APPLICATION_H_
