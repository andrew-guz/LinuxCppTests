#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <Wt/WApplication.h>

class Application final : public Wt::WApplication
{
public:
    Application(const Wt::WEnvironment& env);
};

#endif //_APPLICATION_H_
