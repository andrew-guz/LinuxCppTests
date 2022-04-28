#ifndef _APPLICATIONERRORNOTIFIER_H_
#define _APPLICATIONERRORNOTIFIER_H_

#include <string>

#include "Singleton.h"

class ApplicationErrorNotifier final : public Singleton<ApplicationErrorNotifier>
{
public:
    void notify(const std::string& errorMessage);
};

#endif //_APPLICATIONERRORNOTIFIER_H_
