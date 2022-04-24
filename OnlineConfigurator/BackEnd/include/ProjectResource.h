#ifndef _PROJECTRESOURCE_H_
#define _PROJECTRESOURCE_H_

#include "BaseResource.h"

class ProjectResource final : public BaseResource
{
public:
    ProjectResource(Project& project);

    virtual ~ProjectResource() = default;

protected:
    virtual void callbackGet(const std::shared_ptr<restbed::Session> session) override;
};

#endif //_PROJECTRESOURCE_H_
