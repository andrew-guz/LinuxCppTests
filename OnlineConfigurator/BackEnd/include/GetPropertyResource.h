#ifndef _GETPROPERTYRESOURCE_H_
#define _GETPROPERTYRESOURCE_H_

#include "BaseResource.h"

class GetPropertyResource final : public BaseResource
{
public:
    GetPropertyResource(Project& project);

    virtual ~GetPropertyResource() = default;
    
protected:
    virtual void callback(const std::shared_ptr<restbed::Session> session) override;
};

#endif //_GETPROPERTYRESOURCE_H_
