#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_SWPACKAGEINFOSTATETYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_SWPACKAGEINFOSTATETYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

enum class SwPackageInfoStateType : ::UInt8
{
    kTransferring = 0U,
kTransferred = 1U,
kProcessing = 2U,
kProcessed = 3U,

};

}
}
}

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_SWPACKAGEINFOSTATETYPE_H
