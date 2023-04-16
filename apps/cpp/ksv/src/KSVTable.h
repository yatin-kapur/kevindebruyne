#pragma once

#include <iostream>

#include "lib/logger/log.h"
#include "lib/rapidcsv/rapidcsv.h"
#include "lib/kdb/KTable.h"

class KSVTable: public KTable
{
public:
    KSVTable(const std::string&);
    ~KSVTable();

    void add_pattern(const std::string&);
private:
    Log log;

    std::vector<std::string> m_patterns;
    std::vector<std::string> m_files;
};