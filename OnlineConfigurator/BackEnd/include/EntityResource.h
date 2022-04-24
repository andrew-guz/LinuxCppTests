#ifndef _ENTITYRESOURCE_H_
#define _ENTITYRESOURCE_H_

#include "BaseResource.h"

class EntityResource final : public BaseResource
{
public:
    EntityResource(Project& project);

    virtual ~EntityResource() = default;
    
protected:
    virtual void callbackGet(const std::shared_ptr<restbed::Session> session) override;
};

#endif //_ENTITYRESOURCE_H_
