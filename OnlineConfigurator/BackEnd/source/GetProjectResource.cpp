#include "GetProjectResource.h"

#include <iostream>
#include <nlohmann/json.hpp>

GetProjectResource::GetProjectResource(Project& project) :
    BaseResource(project, "project", "GET")
{

}

void GetProjectResource::callback(const std::shared_ptr<restbed::Session> session)
{
    std::cout << "GetProjectResource: " << session->get_request()->get_path() << std::endl;
    auto jsonObject = nlohmann::json::object();
    jsonObject["id"] = _project.id().data();
    session->close(restbed::OK, jsonObject.dump(4));
}
