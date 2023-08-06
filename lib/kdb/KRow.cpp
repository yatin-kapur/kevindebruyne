#include "KRow.h"

KRow::KRow()
    :log("KRow")
{
    log.info("Constructed KRow");
}

KRow::~KRow()
{
    
}

void KRow::set_colnames(std::vector<std::string> colnames)
{
    m_colnames = colnames;
}
