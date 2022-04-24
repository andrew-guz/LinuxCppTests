#ifndef _CONNECTIONINFORMATION_H_
#define _CONNECTIONINFORMATION_H_

#include "Entity.h"

class ConnectionInformation final : public Entity
{
public:
    ConnectionInformation(bool withSubEntities = true, const Uuid& id = {});

    virtual ~ConnectionInformation() = default;
};

#endif //_CONNECTIONINFORMATION_H_
