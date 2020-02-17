#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_TRANSFEREXITRETURNTYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_TRANSFEREXITRETURNTYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

enum class TransferExitReturnType : ::UInt8
{
    kSuccess = 0U,
kInsufficientData = 1U,
kPackageInconsistent = 2U,
kInvalidTransferId = 3U,
kOperationNotPermitted = 4U,

};

}
}
}

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_TRANSFEREXITRETURNTYPE_H
