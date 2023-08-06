#pragma once

#include <iostream>
#include <vector>
#include <tuple>

#include "lib/logger/log.h"
#include "KRow.h"
#include "KObject.h"

class KTable
{
public:
    KTable(const std::string&);
    ~KTable();

    const std::string& get_table_name();
    
    const std::string& m_tableName;

private:
    Log log;
};