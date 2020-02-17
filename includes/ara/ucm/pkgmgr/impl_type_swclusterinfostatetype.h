#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_SWCLUSTERINFOSTATETYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_SWCLUSTERINFOSTATETYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

enum class SwClusterInfoStateType : ::UInt8
{
    kPresent = 0U,
kAdded = 1U,
kUpdated = 2U,
kRemoved = 3U,

};

}
}
}

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_SWCLUSTERINFOSTATETYPE_H
