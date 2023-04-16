#pragma once

#include <iostream>

#include "lib/logger/log.h"
#include "lib/rapidcsv/rapidcsv.h"
#include "lib/kdb/KTable.h"

class KSVTable: public KTable
{
public:
    typedef std::function<void(const std::string&, std::unique_ptr<KRow>)> TableCallback;

    explicit KSVTable(const TableCallback&, const std::string&);
    ~KSVTable();

    void add_pattern(const std::string&);
    void process_file(const std::string&);
    void process_files();
private:
    Log log;

    std::vector<std::string> m_patterns;
    std::vector<std::string> m_files;

    TableCallback datacallback;
};