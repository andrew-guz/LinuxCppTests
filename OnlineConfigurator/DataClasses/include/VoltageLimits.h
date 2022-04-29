#ifndef _VOLTAGELIMITS_H_
#define _VOLTAGELIMITS_H_

#include "Entity.h"

class VoltageLimits final : public Entity
{
public:
    VoltageLimits(bool withSubEntities = true, const Uuid& id = {});

    virtual ~VoltageLimits() = default;
};

#endif //_VOLTAGELIMITS_H_
