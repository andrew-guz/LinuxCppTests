#include "GetEntityResource.h"

GetEntityResource::GetEntityResource(Project& project) :
    BaseResource(project, "entity/{id: .*}", "GET")
{

}

void GetEntityResource::callback(const std::shared_ptr<restbed::Session> session)
{
    const auto request = session->get_request();
    auto header = request->get_header("id");
    int trap = 0;
    ++trap;
    session->close(restbed::OK, "");
}
