#include "HttpClientUser.h"

#include <cassert>

using namespace Wt;

HttpClientUser::HttpClientUser()
{
    _client.done().connect(std::bind(&HttpClientUser::requestDone, this, std::placeholders::_1, std::placeholders::_2));
}

void HttpClientUser::registerRequestDoneFunction(const std::string& requestName, RequestDoneFunction func)
{
    auto iter = _requestDoneFunections.find(requestName);
    assert(iter == _requestDoneFunections.end());
    if(iter == _requestDoneFunections.end())
        _requestDoneFunections.emplace(requestName, func);
}

bool HttpClientUser::get(const std::string& requestName, const std::string& url)
{
    _requestName = requestName;
    return _client.get(url);
}

bool HttpClientUser::post(const std::string& requestName, const std::string& url, const Http::Message& message)
{
    _requestName = requestName;
    return _client.post(url, message);
}

void HttpClientUser::requestDone(AsioWrapper::error_code errorCode, const Http::Message& message)
{
    auto iter = _requestDoneFunections.find(_requestName);
    assert(iter != _requestDoneFunections.end());
    if (iter != _requestDoneFunections.end())
        (iter->second)(errorCode, message);
}
