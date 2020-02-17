#ifndef ARA_EXEC_IMPL_TYPE_PROCESSSTATE_H
#define ARA_EXEC_IMPL_TYPE_PROCESSSTATE_H

namespace ara
{
namespace exec
{

enum class ProcessState : uint8_t
{
	Idle = 0,
	Starting = 1,
    Running = 2,
    Terminating = 3,
	Terminated = 4,
    Verifying =5   
};

} // namespace exec
} // namespace ara

#endif // ARA_EXEC_IMPL_TYPE_PROCESSSTATE_H

