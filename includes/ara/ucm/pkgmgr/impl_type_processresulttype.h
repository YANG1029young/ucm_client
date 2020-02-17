#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_PROCESSRESULTTYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_PROCESSRESULTTYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

enum class ProcessResultType : ::UInt8
{
    kSuccess = 0U,
kReject = 1U,
kInvalidManifest = 2U,
kPackageInconsistent = 3U,
kInsufficientMemory = 4U,
kInvalidTransferId = 5U,
kOperationNotPermitted = 6U,

};

}
}
}

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_PROCESSRESULTTYPE_H
