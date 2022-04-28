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

protected:
    void registerRequestDoneFunction(const std::string& requestName, RequestDoneFunction func);

    bool get(const std::string& requestName, const std::string& url);

    bool post(const std::string& requestName, const std::string& url, const Wt::Http::Message& message);

private:
    void requestDone(Wt::AsioWrapper::error_code errorCode, const Wt::Http::Message& message);

private:
    Wt::Http::Client                            _client;
    std::map<std::string, RequestDoneFunction>  _requestDoneFunections;
    std::string                                 _requestName;
};

#endif //_HTTPCLIENTUSER_H_
