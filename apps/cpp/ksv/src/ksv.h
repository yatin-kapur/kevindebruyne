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

    void start_tables();
    void callback(const std::string&, std::unique_ptr<KRow>);
    void run();
private:
    Log log;

    const std::string m_configFile;
    pugi::xml_document m_config;

    std::unordered_map<std::string, std::unique_ptr<KSVTable>> m_KSVTables;

    I handle; 
};