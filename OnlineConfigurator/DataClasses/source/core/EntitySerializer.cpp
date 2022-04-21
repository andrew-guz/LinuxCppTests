#include "EntitySerializer.h"

#include <nlohmann/json.hpp>

/*
   auto jsonObject = json::object();
    jsonObject["mainAddress"] = connectionInfo._mainAddress;
    jsonObject["additionalAddress"] = connectionInfo._additionalAddress;
    jsonObject["password"] = connectionInfo._password;
    return jsonObject.dump(4);

    auto jsonObject = json::parse(str);
    return ConnectionInfo{
        jsonObject["mainAddress"].get<std::string>(),
        jsonObject["additionalAddress"].get<std::string>(),
        jsonObject["password"].get<std::string>(),
    };

*/

std::string EntitySerializer::toString(const IEntity* entity)
{
    return "";
}

IEntity* EntitySerializer::toEntity(const std::string& str)
{
    return nullptr;
}
