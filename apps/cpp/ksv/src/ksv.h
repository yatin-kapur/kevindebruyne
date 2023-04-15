#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "lib/logger/log.h"
#include "lib/xmlparse/pugixml.h"
#include "lib/boost/algorithm/string.hpp"
#include "KSVWriter.h"

class KSV
{
public:
    KSV(const std::string&);
    ~KSV();

    void registerWriter(std::string);
    void parseCsvFile();
    void run();
private:
    const std::string m_configFile;
    pugi::xml_document m_config;

    const std::vector<std::shared_ptr<KSVWriter>> m_ksvWriters;

    Log log;
};