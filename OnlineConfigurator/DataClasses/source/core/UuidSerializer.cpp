#include "UuidSerializer.h"

nlohmann::json UuidSerializer::toJson(const Uuid& id)
{
    auto jsonObject = nlohmann::json::object();
    jsonObject["id"] = id.data();
    return jsonObject;
}

Uuid UuidSerializer::fromJson(const nlohmann::json& json)
{
    auto str = json["id"].get<std::string>();    
    return Uuid(str);
}
