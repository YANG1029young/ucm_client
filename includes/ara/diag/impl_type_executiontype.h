#ifndef ARA_DIAG_IMPL_TYPE_EXECUTIONTYPE_H
#define ARA_DIAG_IMPL_TYPE_EXECUTIONTYPE_H

#include "impl_type_uint8.h"

namespace ara
{
namespace diag
{

enum class ExecutionType : ::UInt8
{
    kImmediate=0x00,
kDefered=0x01,

};

}
}

#endif // ARA_DIAG_IMPL_TYPE_EXECUTIONTYPE_H
