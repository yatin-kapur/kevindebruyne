#include "KTable.h"

KTable::KTable(const std::string& tableName):
    m_tableName(tableName),
    log("KTable")
{
    log.info("Constructed KTable.");
}

KTable::~KTable() 
{

}

const std::string& KTable::get_table_name()
{
    return m_tableName;
}