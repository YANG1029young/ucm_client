#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_LOGLEVELTYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_LOGLEVELTYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

enum class LogLevelType : ::UInt8
{
    kOff = 0U,
kFatal = 1U,
kError = 2U,
kWarning = 3U,
kInfo = 4U,
kDebug = 5U,
kVerbose = 6U,

};

}
}
}

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_LOGLEVELTYPE_H
