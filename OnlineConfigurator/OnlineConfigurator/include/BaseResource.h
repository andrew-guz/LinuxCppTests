#ifndef _BASERESOURCE_H_
#define _BASERESOURCE_H_

#include <restbed>

#include "Project.h"

class BaseResource : public restbed::Resource
{
public:
    BaseResource(Project& project, const std::string& path, const std::string& method);

    virtual ~BaseResource() = default;

protected:
    virtual void callback(const std::shared_ptr<restbed::Session> session) = 0;

protected:
    Project& _project;
};


#endif //_BASERESOURCE_H_
