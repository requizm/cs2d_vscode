#ifndef JSONLOADER_H
#define JSONLOADER_H

#include <nlohmann/json.hpp>

class JSONLoader
{
   public:
    JSONLoader() = default;
    ~JSONLoader() = default;

    nlohmann::json Load(const std::string &str);
};

#endif  // JSONLOADER_H