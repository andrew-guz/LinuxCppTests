#ifndef _PROPERTYRESOURCE_H_
#define _PROPERTYRESOURCE_H_

#include "BaseResource.h"

class PropertyResource final : public BaseResource
{
public:
    PropertyResource(Project& project);

    virtual ~PropertyResource() = default;
    
protected:
    virtual void callbackGet(const std::shared_ptr<restbed::Session> session) override;

    virtual void callbackPut(const std::shared_ptr<restbed::Session> session) override;
};

#endif //_PROPERTYRESOURCE_H_
