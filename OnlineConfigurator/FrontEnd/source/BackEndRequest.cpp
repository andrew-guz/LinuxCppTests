#include "BackEndRequest.h"

#include <chrono>

#include <Wt/WApplication.h>
#include <Wt/WMessageBox.h>

#include "WaitingWindow.h"

using namespace Wt;
using namespace Wt::Http;

void BackEndRequest::get(const std::string& path, const std::string& text)
{
    //WaitingWindow::instance()->show(text);
    WMessageBox::show("Confirm", "1", StandardButton::Ok);

    _client = WApplication::instance()->addChild(std::make_unique<Client>());
    _client->setTimeout(std::chrono::seconds{3});
    _client->done().connect([=](Wt::AsioWrapper::error_code err, Message response){
        //WaitingWindow::instance()->close();
        WMessageBox::show("Confirm", "2", StandardButton::Ok);
    });
    if (!_client->get(path))
    {
        WMessageBox::show("Confirm", "3", StandardButton::Ok);
    }
}