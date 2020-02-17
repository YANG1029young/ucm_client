#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_REVERTPROCESSEDSWPACKAGESRETURNTYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_REVERTPROCESSEDSWPACKAGESRETURNTYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

enum class RevertProcessedSwPackagesReturnType : ::UInt8
{
    kSuccess = 0U,
kNothingToRevert = 1U,
kNotAbleToRevertPackages = 2U,

};

}
}
}

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_REVERTPROCESSEDSWPACKAGESRETURNTYPE_H
