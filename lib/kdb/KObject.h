#pragma once

#include <iostream>
#include <unordered_map>
#include "lib/logger/log.h"
#include "lib/k/k.h"

struct kdb_types
{
    enum type {
        // these are all just integers that are placed wherever the "I" 
        // variable is used
        kboolean = KB,
        kint = KI,
        klong = KJ,
        kfloat = KF,
        kchar = KC,
        ksymbol = KS,
        kdate = KD
    };

    // methods
    static type get_type(std::string);

    template <typename T>
    K build_kdb_type(kdb_types::type, T data);
};

class KObject
{
public:
    KObject(const std::string&);
    ~KObject();
private:
    Log log;

    kdb_types::type m_type;
    K m_data;
};