#pragma once

#include <iostream>
#include <vector>
#include "lib/logger/log.h"
// #include "KObject.h"
#include "lib/k/k.h"

class KRow
{
public:
    KRow();
    ~KRow();
private:
    Log log;

    std::vector<std::shared_ptr<K>> m_fields;
};