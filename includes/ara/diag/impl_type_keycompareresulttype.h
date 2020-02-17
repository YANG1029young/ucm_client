#ifndef ARA_DIAG_IMPL_TYPE_KEYCOMPARERESULTTYPE_H
#define ARA_DIAG_IMPL_TYPE_KEYCOMPARERESULTTYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace diag
{

enum class KeyCompareResultType : ::UInt8
{
    kKeyValid=0x00,
kKeyInvalid=0x01,

};

}
}

#endif // ARA_DIAG_IMPL_TYPE_KEYCOMPARERESULTTYPE_H
