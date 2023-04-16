#include "KSVTable.h"

KSVTable::KSVTable(const std::string& tableName)
    :KTable(tableName),
    log("KSVTable")
{
    log.info("constructed KSVTable with name: " + tableName);
}

KSVTable::~KSVTable() 
{

}

void KSVTable::add_pattern(const std::string& p)
{
    m_patterns.push_back(p);
    log.info("for " + get_table_name() + ", set added file pattern: " + p);
};