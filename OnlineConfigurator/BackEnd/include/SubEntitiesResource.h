#ifndef _SUBENTITIESRESOURCE_H_
#define _SUBENTITIESRESOURCE_H_

#include "BaseResource.h"

class SubEntitiesResource final : public BaseResource
{
public:
    SubEntitiesResource(Project& project);

    virtual ~SubEntitiesResource() = default;
    
protected:
    virtual void callbackGet(const std::shared_ptr<restbed::Session> session) override;
};

#endif //_SUBENTITIESRESOURCE_H_
