#ifndef ARA_DIAG_IMPL_TYPE_INITMONITORREASONTYPE_H
#define ARA_DIAG_IMPL_TYPE_INITMONITORREASONTYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace diag
{

enum class InitMonitorReasonType : ::UInt8
{
    kClear=0,
kRestart=1,
kReenabled=2,
kStorageEnabled=3,

};

}
}

#endif // ARA_DIAG_IMPL_TYPE_INITMONITORREASONTYPE_H
