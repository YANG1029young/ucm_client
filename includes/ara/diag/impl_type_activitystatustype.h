#ifndef ARA_DIAG_IMPL_TYPE_ACTIVITYSTATUSTYPE_H
#define ARA_DIAG_IMPL_TYPE_ACTIVITYSTATUSTYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace diag
{

enum class ActivityStatusType : ::UInt8
{
    kActive=0x00,
kInactive=0x01,

};

}
}

#endif // ARA_DIAG_IMPL_TYPE_ACTIVITYSTATUSTYPE_H
