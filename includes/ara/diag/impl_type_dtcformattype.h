#ifndef ARA_DIAG_IMPL_TYPE_DTCFORMATTYPE_H
#define ARA_DIAG_IMPL_TYPE_DTCFORMATTYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace diag
{

enum class DTCFormatType : ::UInt8
{
    kDTCFormatOBD=0,
kDTCFormatUDS=1,
kDTCFormatJ1939=2,

};

}
}

#endif // ARA_DIAG_IMPL_TYPE_DTCFORMATTYPE_H
