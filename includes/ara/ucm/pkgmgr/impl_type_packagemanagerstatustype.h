#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_PACKAGEMANAGERSTATUSTYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_PACKAGEMANAGERSTATUSTYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

enum class PackageManagerStatusType : ::UInt8
{
    kIdle = 0U,
kReady = 1U,
kBusy = 2U,
kActivating = 3U,
kActivated = 4U,
kRollingBack = 5U,
kRolledBack = 6U,
kCleaningUp = 7U,
kFailed = 8U,

};

}
}
}

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_PACKAGEMANAGERSTATUSTYPE_H
