#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <map>

#include "IEntity.h"

#define SET_TYPE(TYPE) static const std::string _type = TYPE;

class Entity : public IEntity
{
public:
    Entity(const std::string& type, bool withSubEntities = true, const Uuid& id = {});

    Entity(const Entity& other) = delete;

    virtual ~Entity();

    virtual const std::string& type() const override final;

    virtual const Uuid& id() const override final;

    virtual std::vector<std::string> listPropertyNames() const override final;

    virtual bool hasProperty(const std::string& name) const override final;

    virtual Property& property(const std::string& name) override  final;

    virtual const Property& property(const std::string& name) const override final;

    virtual const Variant& propertyValue(const std::string& name) const override final;

    virtual std::vector<std::string> listSubEntityNames() const override final;

    virtual bool hasSubEntity(const std::string& name) const override final;

    virtual IEntity* subEntity(const std::string& name) override final;

    virtual const IEntity* subEntity(const std::string& name) const override final;

protected:
    void addProperty(const std::string& name, const std::string& displayName, const Variant& data = {});

    template<typename T>
    void addSubEntity(const std::string& name)
    {
        if(_withSubEntities)
            _subEntities.emplace(name, new T(true));
    }

private:
    const std::string               _type;
    bool                            _withSubEntities;
    Uuid                            _id;
    std::map<std::string, Property> _properties;
    std::map<std::string, IEntity*> _subEntities;

private:
    friend class EntitySerializer;
};

#endif //_ENTITY_H_
