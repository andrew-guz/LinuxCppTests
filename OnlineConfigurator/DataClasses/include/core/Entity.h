#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <map>

#include "IEntity.h"

class Entity : public IEntity
{
public:
    Entity() = default;

    Entity(const Uuid& id);

    virtual ~Entity();

public:
    virtual const Uuid& id() const override final;

    virtual std::vector<std::string> listPropertyNames() const override final;

    virtual Property& property(const std::string& name) override  final;

    virtual const Property& property(const std::string& name) const override final;

    virtual std::vector<std::string> listSubEntityNames() const override final;

    virtual IEntity* subEntity(const std::string& name) override final;

    virtual const IEntity* subEntity(const std::string& name) const override final;

protected:
    void addProperty(const std::string& name, const std::string& displayName, const Variant& data = {});

    void addSubEntity(const std::string& name, IEntity* entity);

private:
    Uuid                            _id;
    std::map<std::string, Property> _properties;
    std::map<std::string, IEntity*> _subEntities;

private:
    friend class EntitySerializer;
};

#endif //_ENTITY_H_
