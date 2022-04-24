#ifndef _GETENTITYRESOURCE_H_
#define _GETENTITYRESOURCE_H_

#include "BaseResource.h"

class GetEntityResource final : public BaseResource
{
public:
    GetEntityResource(Project& project);

    virtual ~GetEntityResource() = default;
    
protected:
    virtual void callback(const std::shared_ptr<restbed::Session> session) override;
};

#endif //_GETENTITYRESOURCE_H_
