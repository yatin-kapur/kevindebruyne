#pragma once

#include <iostream>
#include <vector>
#include "lib/logger/log.h"
#include "KObject.h"

class KRow
{
public:
    KRow();
    ~KRow();
private:
    Log log;

    std::vector<std::shared_ptr<KObject>> m_fields;
};