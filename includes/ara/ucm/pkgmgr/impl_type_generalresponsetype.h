#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_GENERALRESPONSETYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_GENERALRESPONSETYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

enum class GeneralResponseType : ::UInt8
{
    kSuccess = 0U,
kGeneralReject = 1U,
kGeneralMemoryError = 2U,
kTransferIdInvalid = 3U,
kOperationNotPermitted = 4U,

};

}
}
}

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_GENERALRESPONSETYPE_H
