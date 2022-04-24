#ifndef _GETENTITYSUBENTITIESRESOURCE_H_
#define _GETENTITYSUBENTITIESRESOURCE_H_

#include "BaseResource.h"

class GetEntitySubEntitiesResource final : public BaseResource
{
public:
    GetEntitySubEntitiesResource(Project& project);

    virtual ~GetEntitySubEntitiesResource() = default;
    
protected:
    virtual void callback(const std::shared_ptr<restbed::Session> session) override;
};

#endif //_GETENTITYSUBENTITIESRESOURCE_H_
