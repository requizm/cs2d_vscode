#include "XMLLoader.hpp"

XMLLoader::XMLLoader(std::string &mapName)
{
    Load(mapName);
}

XMLLoader::~XMLLoader()
{
    delete[] codeChar;
}

void XMLLoader::Load(std::string &mapName)
{
    std::string codeString;
    std::ifstream fileC(mapName.c_str());
    if (!fileC)
    {
        LOG_ERROR("dosya acilamadi: " + mapName);
        Logger::WriteLog("dosya acilamadi: " + mapName);
        exit(EXIT_FAILURE);
    }

    std::stringstream fileStream;
    fileStream << fileC.rdbuf();
    fileC.close();
    codeString = fileStream.str();
    codeChar = new char[codeString.length() + 1];
    strcpy(codeChar, codeString.c_str());
    doc.parse<0>(codeChar);
}

rapidxml::xml_document<> &XMLLoader::GetDoc()
{
    return doc;
}
