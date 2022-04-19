#ifndef _CONNECTIONINFOJSON_H_
#define _CONNECTIONINFOJSON_H_

#include <string>
#include <nlohmann/json.hpp>

#include "DataJson.h"
#include "ConnectionInfo.h"

using namespace nlohmann;

template<>
std::string DataJson<ConnectionInfo>::ToJson(const ConnectionInfo& connectionInfo)
{
    auto jsonObject = json::object();
    jsonObject["mainAddress"] = connectionInfo._mainAddress;
    jsonObject["additionalAddress"] = connectionInfo._additionalAddress;
    jsonObject["password"] = connectionInfo._password;
    return jsonObject.dump(4);
}

template<>
ConnectionInfo DataJson<ConnectionInfo>::FromJson(const std::string& str)
{
    auto jsonObject = json::parse(str);
    return ConnectionInfo{
        jsonObject["mainAddress"].get<std::string>(),
        jsonObject["additionalAddress"].get<std::string>(),
        jsonObject["password"].get<std::string>(),
    };
}

#endif //_CONNECTIONINFOJSON_H_