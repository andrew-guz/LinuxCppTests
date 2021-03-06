#ifndef _URLBUILDER_H_
#define _URLBUILDER_H_

#include <string>

#include "Uuid.h"
#include "Singleton.h"

class UrlBuilder final : public Singleton<UrlBuilder>
{
public:
    void init(int port);

    std::string projectUrl() const;

    std::string subEntitiesUrl(const Uuid& id) const;

    std::string subEntitiesUrl(const std::string& id) const;

    std::string entityUrl(const Uuid& id) const;

    std::string entityUrl(const std::string& id) const;

    std::string propertyUrl(const Uuid& id, const std::string& propertyName) const;

    std::string propertyUrl(const std::string& id, const std::string& propertyName) const;

private:
    int             _port = -1;
    mutable char    _buffer[1000];
};

#endif //_URLBUILDER_H_
