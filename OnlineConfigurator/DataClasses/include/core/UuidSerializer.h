#ifndef _UUIDSERIALIZER_H
#define _UUIDSERIALIZER_H

#include <nlohmann/json.hpp>

#include "Uuid.h"

class UuidSerializer final
{
public:
    virtual ~UuidSerializer() = default;

    static nlohmann::json toJson(const Uuid& id);

    static Uuid fromJson(const nlohmann::json& json);
};

#endif //_UUIDSERIALIZER_H
