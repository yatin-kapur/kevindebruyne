#include "KObject.h"

static std::unordered_map<char, kdb_types::type> kdb_type_map = {
    {   'b',    kdb_types::type::kboolean },
    {   'u',    kdb_types::type::kguid    },
    {   'g',    kdb_types::type::kbyte    },
    {   'h',    kdb_types::type::kshort   },
    {   'i',    kdb_types::type::kint     },
    {   'j',    kdb_types::type::klong    },
    {   'e',    kdb_types::type::kreal    },
    {   'f',    kdb_types::type::kfloat   },
    {   'c',    kdb_types::type::kchar    },
    {   's',    kdb_types::type::ksymbol  },
    {   'p',    kdb_types::type::ktimestamp   },
    {   'm',    kdb_types::type::kmonth   },
    {   'd',    kdb_types::type::kdate    },
    {   'n',    kdb_types::type::ktimespan    },
    {   'u',    kdb_types::type::kminute  },
    {   'v',    kdb_types::type::ksecond  },
    {   't',    kdb_types::type::ktime    },
    {   'z',    kdb_types::type::kdatetime    }
};


KObject::KObject(char t)
    :log("KObject"),
    m_type(kdb_types::get_type(t))
{

}

KObject::~KObject()
{

}

kdb_types::type kdb_types::get_type(char t){ return kdb_type_map.find(t)->second; }
