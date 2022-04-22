#include <iostream>
#include <memory>
#include <cstdlib>

#include <restbed>

void get_method_handler(const std::shared_ptr<restbed::Session> session)
{
    session->close(restbed::OK, "Hello, World!", { { "Content-Length", "13" } });
}

int main()
{
    auto resource = std::make_shared<restbed::Resource>();
    resource->set_path("/hello");
    resource->set_method_handler("GET", get_method_handler);

    auto settings = std::make_shared<restbed::Settings>();
    settings->set_port(8080);
    settings->set_default_header("Connection", "close");

    restbed::Service service;
    service.publish(resource);
    service.start(settings);

    return 0;
}
