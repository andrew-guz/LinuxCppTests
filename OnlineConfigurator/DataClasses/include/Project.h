#ifndef _PROJECT_H_
#define _PROJECT_H_

#include "Entity.h"

class Project final : public Entity
{
public:
    Project(bool withSubEntities = true, const Uuid& id = {});

    virtual ~Project() = default;
};

#endif //_PROJECT_H_
