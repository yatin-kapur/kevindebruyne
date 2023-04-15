#include <iostream>

#include "lib/logger/log.h"
#include "lib/rapidcsv/rapidcsv.h"

class KSV
{
public:
    KSV(std::string);

private:
    std::string m_csvFile;
    std::string m_qhost;
    std::string m_qport;

    Log log;
};