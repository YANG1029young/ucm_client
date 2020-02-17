#ifndef ARA_EXEC_IMPL_TYPE_STATECHANGESTATUS_H
#define ARA_EXEC_IMPL_TYPE_STATECHANGESTATUS_H

namespace ara
{
namespace exec
{

enum class StateChangeStatus : uint8_t
{
    kSuccess,
    kFailed,
    kTimeout
};

} // namespace exec
} // namespace ara

#endif // ARA_EXEC_IMPL_TYPE_STATECHANGESTATUS_H

