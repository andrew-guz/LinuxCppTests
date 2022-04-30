#include "HttpClientUser.h"

#include <cassert>

#include "WaitingWindow.h"
#include "ApplicationErrorNotifier.h"

using namespace Wt;

HttpClientUser::HttpClientUser()
{
    _client.done().connect(std::bind(&HttpClientUser::requestDone, this, std::placeholders::_1, std::placeholders::_2));
}

void HttpClientUser::registerRequestDoneFunction(const std::string& requestName, RequestDoneFunction func)
{
    auto iter = _requestDoneFunctions.find(requestName);
    assert(iter == _requestDoneFunctions.end());
    if(iter == _requestDoneFunctions.end())
        _requestDoneFunctions.emplace(requestName, func);
}

void HttpClientUser::get(const std::string& requestName, const std::string& url)
{
    _requestName = requestName;
    if (_client.get(url))
        WaitingWindow::instance()->show();
    else
        requestFailed();
}

void HttpClientUser::post(const std::string& requestName, const std::string& url, const std::string& body)
{
    Http::Message message;
    message.addBodyText(body);
    post(requestName, url, message);
}

void HttpClientUser::post(const std::string& requestName, const std::string& url, const Http::Message& message)
{
    _requestName = requestName;
    if (_client.post(url, message))
        WaitingWindow::instance()->show();
    else
        requestFailed();
}

void HttpClientUser::put(const std::string& requestName, const std::string& url, const std::string& body)
{
    Http::Message message;
    message.addBodyText(body);
    put(requestName, url, message);
}

void HttpClientUser::put(const std::string& requestName, const std::string& url, const Wt::Http::Message& message)
{
    _requestName = requestName;
    if (_client.put(url, message))
        WaitingWindow::instance()->show();
    else
        requestFailed();
}

void HttpClientUser::requestFailed()
{
    ApplicationErrorNotifier::instance()->notify(u8"Ошибка сетевого взаимодействия");
}

void HttpClientUser::requestDone(AsioWrapper::error_code errorCode, const Http::Message& message)
{
    WaitingWindow::instance()->hide();
    auto iter = _requestDoneFunctions.find(_requestName);
    assert(iter != _requestDoneFunctions.end());
    if (iter != _requestDoneFunctions.end())
        (iter->second)(errorCode, message);
}
