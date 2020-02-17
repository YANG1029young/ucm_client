#ifndef ARA_DIAG_IMPL_TYPE_MONITORACTIONTYPE_H
#define ARA_DIAG_IMPL_TYPE_MONITORACTIONTYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace diag
{

enum class MonitorActionType : ::UInt8
{
    kPassed=0,
kFailed=1,
kPrepassed=2,
kPrefailed=3,
kFdcThresholdReached=4,
kResetTestFailed=5,
kFreezeDebouncing=6,
kResetDebouncing=7,
kPrestore=8,
kClearPrestore=9,

};

}
}

#endif // ARA_DIAG_IMPL_TYPE_MONITORACTIONTYPE_H
