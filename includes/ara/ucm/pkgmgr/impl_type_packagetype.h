#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_PACKAGETYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_PACKAGETYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

enum class PackageType : ::UInt8
{
    kApplication = 1U,
kPlatform = 2U,
kLibrary = 3U,

};

}
}
}

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_PACKAGETYPE_H
