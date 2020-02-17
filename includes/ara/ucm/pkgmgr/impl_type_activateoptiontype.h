#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_ACTIVATEOPTIONTYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_ACTIVATEOPTIONTYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

enum class ActivateOptionType : ::UInt8
{
    kDefault = 0U,
kFunctionGroupRestart = 1U,
kSystemReset = 2U,

};

}
}
}

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_ACTIVATEOPTIONTYPE_H
