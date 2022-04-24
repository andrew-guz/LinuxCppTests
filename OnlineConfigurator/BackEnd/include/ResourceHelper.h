#ifndef _RESOURCEHELPER_H_
#define _RESOURCEHELPER_H_

#include <restbed>
#include <nlohmann/json.hpp>

#include "IEntity.h"

class ResourceHelper final
{
public:
    static IEntity* getEntity(const std::shared_ptr<restbed::Session> session);

    static IEntity* getEntity(const std::shared_ptr<const restbed::Request> request);

    static nlohmann::json getBodyJson(const std::shared_ptr<restbed::Session> session);
};

#endif //_RESOURCEHELPER_H_
