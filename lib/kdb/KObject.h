#pragma once

#include <iostream>
#include <unordered_map>
#include "lib/logger/log.h"
#include "lib/k/k.h"

struct kdb_types
{
    enum type {
        kboolean = KB,
        kguid = UU,
        kbyte = KG,
        kshort = KH,
        kint = KI,
        klong = KJ,
        kreal = KE,
        kfloat = KF,
        kchar = KC,
        ksymbol = KS,
        ktimestamp = KP,
        kmonth = KM,
        kdate = KD,
        ktimespan = KN,
        kminute = KU,
        ksecond = KV,
        ktime = KT,
        kdatetime = KZ
    };
    
    static type get_type(char t);
};

class KObject
{
public:
    KObject(char);
    ~KObject();
private:
    Log log;

    kdb_types::type m_type;
};