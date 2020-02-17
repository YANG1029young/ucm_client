#ifndef ARA_DIAG_IMPL_TYPE_CONTROLDTCSTATUSTYPE_H
#define ARA_DIAG_IMPL_TYPE_CONTROLDTCSTATUSTYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace diag
{

enum class ControlDTCStatusType : ::UInt8
{
    kDTCSettingOn=0x00,
kDTCSettingOff=0x01,

};

}
}

#endif // ARA_DIAG_IMPL_TYPE_CONTROLDTCSTATUSTYPE_H
