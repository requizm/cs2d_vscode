#include "JSONLoader.hpp"

#include <fstream>

#include "../Manager/Logger.hpp"

nlohmann::json JSONLoader::Load(const std::string &str)
{
    std::ifstream t(str);
    ASSERTM_ERROR(t, "dosya acilamadi: " + str);

    nlohmann::json j;
    t >> j;

    return j;
}