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
