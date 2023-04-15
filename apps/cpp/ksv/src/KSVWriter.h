#pragma once

#include <iostream>

#include "lib/logger/log.h"
#include "lib/rapidcsv/rapidcsv.h"
#include "lib/k/k.h"

class KSVWriter
{
public:
    KSVWriter(std::string);
    ~KSVWriter();

    void write_next();
private:
    std::string m_csvFile;
    
    int m_row = 0;

    Log log;
};