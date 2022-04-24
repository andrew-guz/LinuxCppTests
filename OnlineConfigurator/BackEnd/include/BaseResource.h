#ifndef _BASERESOURCE_H_
#define _BASERESOURCE_H_

#include <restbed>

#include "Project.h"

struct BaseResourceMethodsConfig
{
    bool _get;
    bool _put;
};

class BaseResource : public restbed::Resource
{
public:
    BaseResource(Project& project, const std::string& path, const BaseResourceMethodsConfig& config);

    virtual ~BaseResource() = default;

protected:
    virtual void callbackGet(const std::shared_ptr<restbed::Session> session) { }

    virtual void callbackPut(const std::shared_ptr<restbed::Session> session) { }

protected:
    Project& _project;
};


#endif //_BASERESOURCE_H_
