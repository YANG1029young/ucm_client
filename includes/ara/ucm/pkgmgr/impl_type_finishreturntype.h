#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_FINISHRETURNTYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_FINISHRETURNTYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

enum class FinishReturnType : ::UInt8
{
    kSuccess = 0U,
kUndefinedError = 1U,
kOperationNotPermitted = 2U,

};

}
}
}

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_FINISHRETURNTYPE_H
