#include <iostream>
#include <crow.h>

int main()
{
    crow::SimpleApp app;

    CROW_WEBSOCKET_ROUTE(app, "/ws")
        .onaccept([&](const crow::request& request, void** userData)
        {
            std::cout << "onaccept" << std::endl;
            return true;
        })
        .onopen([&](crow::websocket::connection& connection)
        {
            std::cout << "onopen" << std::endl;
        })
        .onmessage([&](crow::websocket::connection& connection, const std::string& data, bool binary)
        {
            std::cout << "onmessage" << std::endl;
        })
        .onerror([&](crow::websocket::connection& connection, const std::string& error_message)
        {
            std::cout << "onerror" << std::endl;
        })
        .onclose([&](crow::websocket::connection& conn, const std::string& reason)
        {
            std::cout << "onclose" << std::endl;
        });

    app
        .port(7317)
        .multithreaded()
        .run();
    
    return 0;
}
