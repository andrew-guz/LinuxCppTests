#ifndef _GETPROJECTRESOURCE_H_
#define _GETPROJECTRESOURCE_H_

#include "BaseResource.h"

class GetProjectResource final : public BaseResource
{
public:
    GetProjectResource(Project& project);

    virtual ~GetProjectResource() = default;

protected:
    virtual void callback(const std::shared_ptr<restbed::Session> session) override;
};

#endif //_GETPROJECTRESOURCE_H_
