#include "KObject.h"

static std::unordered_map<std::string, kdb_types::type> kdb_type_map = {
    {   "boolean",    kdb_types::type::kboolean },
    {   "int",    kdb_types::type::kint     },
    {   "long",    kdb_types::type::klong    },
    {   "float",    kdb_types::type::kfloat   },
    {   "char",    kdb_types::type::kchar  },
    {   "symbol",    kdb_types::type::ksymbol  },
    {   "date",    kdb_types::type::kdate    }
};

kdb_types::type kdb_types::get_type(std::string t)
{
    return kdb_type_map.find(t)->second; 
}

template <typename T>
K build_kdb_type(kdb_types::type t, T data)
{
    switch (t)
    {
        case kdb_types::type::ksymbol: return ks((S)data);
        default: return krr((S)"na");
    }
}


// KObject ////////////
KObject::KObject(const std::string& t)
    :log("KObject"),
    m_type(kdb_types::get_type(t))
{

}

KObject::~KObject()
{

}