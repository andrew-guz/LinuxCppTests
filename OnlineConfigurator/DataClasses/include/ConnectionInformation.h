#ifndef _CONNECTIONINFORMATION_H_
#define _CONNECTIONINFORMATION_H_

#include "Entity.h"

class ConnectionInformation final : public Entity
{
public:
    ConnectionInformation(const Uuid& id = {});

    virtual ~ConnectionInformation() = default;
};

#endif //_CONNECTIONINFORMATION_H_
