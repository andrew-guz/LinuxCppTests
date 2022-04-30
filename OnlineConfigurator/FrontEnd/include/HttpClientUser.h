#ifndef _HTTPCLIENTUSER_H_
#define _HTTPCLIENTUSER_H_

#include <string>
#include <map>

#include <Wt/Http/Client.h>

typedef std::function<void(Wt::AsioWrapper::error_code, const Wt::Http::Message&)> RequestDoneFunction;

class HttpClientUser
{
public:
    HttpClientUser();

    virtual ~HttpClientUser() = default;

    void registerRequestDoneFunction(const std::string& requestName, RequestDoneFunction func);

    void get(const std::string& requestName, const std::string& url);

    void post(const std::string& requestName, const std::string& url, const std::string& body);

    void post(const std::string& requestName, const std::string& url, const Wt::Http::Message& message);

    void put(const std::string& requestName, const std::string& url, const std::string& body);

    void put(const std::string& requestName, const std::string& url, const Wt::Http::Message& message);

private:
    void requestFailed();

    void requestDone(Wt::AsioWrapper::error_code errorCode, const Wt::Http::Message& message);

private:
    Wt::Http::Client                            _client;
    std::map<std::string, RequestDoneFunction>  _requestDoneFunctions;
    std::string                                 _requestName;
};

#endif //_HTTPCLIENTUSER_H_
