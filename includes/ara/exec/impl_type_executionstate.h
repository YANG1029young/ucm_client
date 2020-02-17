#ifndef ARA_EXEC_IMPL_TYPE_EXECUTIONSTATE_H
#define ARA_EXEC_IMPL_TYPE_EXECUTIONSTATE_H

namespace ara
{
namespace exec
{

enum class ExecutionState : uint8_t
{
    kRunning = 0,
    kTerminating = 1
};

} // namespace exec
} // namespace ara

#endif // ARA_EXEC_IMPL_TYPE_EXECUTIONSTATE_H

