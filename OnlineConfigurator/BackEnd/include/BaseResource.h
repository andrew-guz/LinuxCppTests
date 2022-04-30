#ifndef _BASERESOURCE_H_
#define _BASERESOURCE_H_

#include <restbed>

#include "Project.h"

struct BaseResourceMethodsConfig
{
    bool _get;
    bool _post;
    bool _put;
    bool _delete;
};

class BaseResource : public restbed::Resource
{
public:
    BaseResource(Project& project, const std::string& path, const BaseResourceMethodsConfig& config);

    virtual ~BaseResource() = default;

protected:
    virtual void callbackGet(const std::shared_ptr<restbed::Session> session) { }

    virtual void callbackPost(const std::shared_ptr<restbed::Session> session) { }

    virtual void callbackPut(const std::shared_ptr<restbed::Session> session) { }

    virtual void callbackDelete(const std::shared_ptr<restbed::Session> session) { }

protected:
    Project& _project;
};


#endif //_BASERESOURCE_H_
