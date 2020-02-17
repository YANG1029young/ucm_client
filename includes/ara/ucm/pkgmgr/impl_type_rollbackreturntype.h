#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_ROLLBACKRETURNTYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_ROLLBACKRETURNTYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

enum class RollbackReturnType : ::UInt8
{
    kSuccess = 0U,
kNothingToRollback = 1U,
kNotAbleToRollback = 2U,

};

}
}
}

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_ROLLBACKRETURNTYPE_H
