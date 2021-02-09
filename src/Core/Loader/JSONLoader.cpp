#include "JSONLoader.hpp"

JSONLoader::JSONLoader()
{
}

JSONLoader::~JSONLoader()
{
}

nlohmann::json JSONLoader::Load(std::string &str)
{
    std::ifstream t(str);
    if (!t)
    {
        WRITE_ERROR("dosya acilamadi: " + str);
        exit(EXIT_FAILURE);
    }

    nlohmann::json j;
    t >> j;

    for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it)
    {
        LOG_INFO(it->at("name"));
    }

    return j;
}