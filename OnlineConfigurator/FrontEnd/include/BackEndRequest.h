#ifndef _BACKENDREQUEST_H_
#define _BACKENDREQUEST_H_

#include <nlohmann/json.hpp>
#include <Wt/WObject.h>

#include <Wt/Http/Client.h>

class BackEndRequest final : Wt::WObject
{
public:
    virtual ~BackEndRequest() = default;

    void get(const std::string& path, const std::string& text = {});

private:
    Wt::Http::Client* _client = nullptr;
};

#endif //_BACKENDREQUEST_H_
