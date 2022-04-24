#include "ProjectResource.h"

#include <iostream>
#include <nlohmann/json.hpp>

ProjectResource::ProjectResource(Project& project) :
    BaseResource(project, "project", { true, false })
{

}

void ProjectResource::callbackGet(const std::shared_ptr<restbed::Session> session)
{
    std::cout << "ProjectResource GET: " << session->get_request()->get_path() << std::endl;
    auto jsonObject = nlohmann::json::object();
    jsonObject["id"] = _project.id().data();
    session->close(restbed::OK, jsonObject.dump(4));
}
