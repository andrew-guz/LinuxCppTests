#ifndef _UPDATEPROPERTYRESOURCE$_H_
#define _UPDATEPROPERTYRESOURCE$_H_

#include "BaseResource.h"

class UpdatePropertyResource final : public BaseResource
{
public:
    UpdatePropertyResource(Project& project);

    virtual ~UpdatePropertyResource() = default;
    
protected:
    virtual void callback(const std::shared_ptr<restbed::Session> session) override;
};


#endif //_UPDATEPROPERTYRESOURCE$_H_
