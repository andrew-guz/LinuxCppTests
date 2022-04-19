#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <uuid/uuid.h>

class Entity
{
public:
    Entity();

    Entity(const uuid_t& id);

    virtual ~Entity() = default;

public:
    const uuid_t& id() const;

private:
    uuid_t _id;
};

#endif //_ENTITY_H_
