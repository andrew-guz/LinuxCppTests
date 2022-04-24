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

nlohmann::json ResourceHelper::getBodyJson(const std::shared_ptr<restbed::Session> session)
{
    const auto request = session->get_request();
    if (request->has_header("Content-Length"))
    {
        auto contentLengthStr = request->get_header("Content-Length", "0");
        std::size_t contentLength = 0;
        try
        {
            contentLength = std::stoi(contentLengthStr);
        }
        catch(...)
        {
            return {};
        }
        if (contentLength > 0)
        {
            std::string jsonStr;
            session->fetch(contentLength, [&jsonStr](const std::shared_ptr<restbed::Session> session, const restbed::Bytes& body)
            {
                jsonStr = restbed::String::to_string(body);
            });
            if (jsonStr.size())
            {
                try
                {
                    return nlohmann::json::parse(jsonStr);
                }
                catch(...)
                {
                    return {};
                }

            }
        }
    }
    return {};
}
