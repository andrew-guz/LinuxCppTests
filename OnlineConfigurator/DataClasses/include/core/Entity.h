#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <map>

#include "IEntity.h"

class Entity : public IEntity
{
public:
    Entity();

    Entity(const uuid_t& id);

    virtual ~Entity();

public:
    virtual const uuid_t& id() const override;

    virtual Property& operator[](const std::string& name) override;

    virtual const Property& operator[](const std::string& name) const override;

    virtual IEntity* getSubEntity(const std::string& name) override;

    virtual const IEntity* getSubEntity(const std::string& name) const override;

protected:
    void addProperty(const std::string& name, const std::string& displayName, const Variant& data = {});

    void addSubEntity(const std::string& name, IEntity* entity);

private:
    uuid_t                          _id;
    std::map<std::string, Property> _properties;
    std::map<std::string, IEntity*> _subEntities;
};

#endif //_ENTITY_H_
