#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_TRANSFERDATARETURNTYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_TRANSFERDATARETURNTYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

enum class TransferDataReturnType : ::UInt8
{
    kSuccess = 0U,
kIncorrectBlock = 1U,
kIncorrectSize = 2U,
kInsufficientMemory = 3U,
kInvalidTransferId = 4U,
kOperationNotPermitted = 5U,

};

}
}
}

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_TRANSFERDATARETURNTYPE_H
