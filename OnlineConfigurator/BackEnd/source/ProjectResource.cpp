#include "ProjectResource.h"

#include <iostream>
#include <nlohmann/json.hpp>

ProjectResource::ProjectResource(Project& project) :
    BaseResource(project, "project", { true, false, false, false })
{

}

void ProjectResource::callbackGet(const std::shared_ptr<restbed::Session> session)
{
    std::cout << "ProjectResource GET: " << session->get_request()->get_path() << std::endl;
    auto jsonObject = nlohmann::json::object();
    jsonObject["id"] = _project.id().data();
    auto jsonObjectString = jsonObject.dump(4);
    std::cout << "ProjectResource GET: " << jsonObjectString << std::endl;
    session->close(restbed::OK, jsonObjectString);
}
