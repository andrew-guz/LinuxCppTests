#include "VariantSerializer.h"

#include <cassert>

nlohmann::json VariantSerializer::toJson(const Variant& data)
{
    auto jsonObject = nlohmann::json::object();    
    if (data.isEmpty())
        jsonObject["empty"] = "empty";
    else
    {
        int index = data.typeIndex();
        jsonObject["type"] = index;
        switch (index)
        {
        case 0:
            jsonObject["value"] = data.toBool();
            break;
        case 1:
            jsonObject["value"] = data.toInt();
            break;
        case 2:
            jsonObject["value"] = data.toFloat();
            break;
        case 3:
            jsonObject["value"] = data.toString();
            break;
        default:
            assert(false);
            break;
        }
    }
    return jsonObject;
}

Variant VariantSerializer::fromJson(const nlohmann::json& json)
{
    if (json.contains("empty") ||
        !json.contains("type"))
        return {};
    int type = json["type"];
    switch (type)
    {
    case 0:
        return Variant(json.value<bool>("value", false));
    case 1:
        return Variant(json.value<int>("value", 0));
    case 2:
        return Variant(json.value<float>("value", 0.0f));
    case 3:
        return Variant(json.value<std::string>("value", ""));
    default:
        assert(false);
        break;
    }
    return Variant();
}
