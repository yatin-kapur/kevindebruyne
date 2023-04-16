#pragma once

#include <iostream>
#include <vector>

#include "lib/logger/log.h"
#include "KRow.h"

class KTable
{
public:
    KTable(const std::string&);
    ~KTable();

    const std::string& get_table_name();

    const std::string& m_tableName;
    std::vector<std::shared_ptr<KRow>> m_rows;
private:
    Log log;
};