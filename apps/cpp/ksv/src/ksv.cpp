#include "ksv.h"

KSV::KSV(std::string file)
    : m_csvFile(file),
    log("ksv")
{
    log.info("constructed KSV for csv file at: " + m_csvFile);
}

