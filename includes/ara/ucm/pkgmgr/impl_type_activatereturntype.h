#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_ACTIVATERETURNTYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_ACTIVATERETURNTYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

enum class ActivateReturnType : ::UInt8
{
    kSuccess = 0U,
kErrorNoProcessedPackages = 1U,
kErrorDuringActivation = 2U,
kErrorNoValidProcessing = 3U,
kErrorMissingDependencies = 4U,

};

}
}
}

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_ACTIVATERETURNTYPE_H
