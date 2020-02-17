#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_CANCELRETURNTYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_CANCELRETURNTYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

enum class CancelReturnType : ::UInt8
{
    kSuccess = 0U,
kError = 1U,
kOperationNotPermitted = 2U,

};

}
}
}

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_CANCELRETURNTYPE_H
