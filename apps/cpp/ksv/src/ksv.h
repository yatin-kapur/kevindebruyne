#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "lib/logger/log.h"
#include "lib/xmlparse/pugixml.h"
#include "lib/boost/algorithm/string.hpp"

#include "KSVTable.h"

class KSV
{
public:
    KSV(const std::string&);
    ~KSV();

    void registerWriter(std::string);
    void parseCsvFile();
    void run();
private:
    Log log;

    const std::string m_configFile;
    pugi::xml_document m_config;

    
    std::unordered_map<std::string, std::shared_ptr<KSVTable>> m_KSVTables;

    I handle; 
};