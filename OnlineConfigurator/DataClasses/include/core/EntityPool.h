#ifndef _ENTITYPOOL_H_
#define _ENTITYPOOL_H_

#include <map>

#include "Singleton.h"
#include "IEntity.h"

class EntityPool final : public Singleton<EntityPool>
{
public:
    void add(IEntity* entity);

    void remove(IEntity* entity);

    IEntity* find(const Uuid& id);

    const IEntity* find(const Uuid& id) const;

    template<typename T>
    T* findConcrete(const Uuid& id)
    {
        return dynamic_cast<T*>(find(id));
    }

    template<typename T>
    const T* findConcrete(const Uuid& id) const
    {
        return dynamic_cast<T*>(find(id));
    }

    void disable();

private:
    std::map<Uuid, IEntity*>    _entities;
    bool                        _disabled = false;
};

#endif //_ENTITYPOOL_H_
