#ifndef XMLLOADER_H
#define XMLLOADER_H

#include <rapidxml-1.13/rapidxml.hpp>
#include <rapidxml-1.13/rapidxml_print.hpp>
#include <string>


class XMLLoader
{
   public:
    XMLLoader(std::string &mapName);
    ~XMLLoader();
    rapidxml::xml_document<> &GetDoc();

   private:
    void Load(std::string &mapName);

    rapidxml::xml_document<> doc;
    char *codeChar = nullptr;
};

#endif  // XMLLOADER_H