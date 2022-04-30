#include "UrlBuilder.h"

void UrlBuilder::init(int port)
{
    _port = port;
}

std::string UrlBuilder::projectUrl() const
{
    std::snprintf(_buffer, 1000, "http://127.0.0.1:%i/project", _port);
    return _buffer;
}

std::string UrlBuilder::subEntitiesUrl(const Uuid& id) const
{
    return subEntitiesUrl(id.data());
}

std::string UrlBuilder::subEntitiesUrl(const std::string& id) const
{
    std::snprintf(_buffer, 1000, "http://127.0.0.1:%i/subEntities/%s", _port, id.c_str());
    return _buffer;
}

std::string UrlBuilder::entityUrl(const Uuid& id) const
{
    return entityUrl(id.data());
}

std::string UrlBuilder::entityUrl(const std::string& id) const
{
    std::snprintf(_buffer, 1000, "http://127.0.0.1:%i/entity/%s", _port, id.c_str());
    return _buffer;
}

std::string UrlBuilder::propertyUrl(const std::string& id, const std::string& propertyName) const
{
    std::snprintf(_buffer, 1000, "http://127.0.0.1:%i/property/%s/%s", _port, id.c_str(), propertyName.c_str());
    return _buffer;
}
