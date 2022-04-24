#include "ResourceHelper.h"

#include "EntityPool.h"

IEntity* ResourceHelper::getEntity(const std::shared_ptr<restbed::Session> session)
{
    return ResourceHelper::getEntity(session->get_request());
}

IEntity* ResourceHelper::getEntity(const std::shared_ptr<const restbed::Request> request)
{
    if (request->has_path_parameter("id"))
        return EntityPool::instance()->find(request->get_path_parameter("id"));
    return nullptr;
}

