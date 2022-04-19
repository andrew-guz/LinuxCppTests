#include "Entity.h"

Entity::Entity()
{
    uuid_generate_random(_id);
}

Entity::Entity(const uuid_t& id)
{
    uuid_copy(_id, id);
}

const uuid_t& Entity::id() const
{
    return _id;
}
