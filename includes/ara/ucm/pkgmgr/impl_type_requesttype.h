#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_REQUESTTYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_REQUESTTYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

enum class RequestType : ::UInt8
{
    kInstall = 1U,
kUninstall = 2U,
kUpdate = 3U,

};

}
}
}

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_REQUESTTYPE_H
