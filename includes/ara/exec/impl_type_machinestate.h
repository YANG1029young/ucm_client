#ifndef ARA_EXEC_IMPL_TYPE_MACHINESTATE_H
#define ARA_EXEC_IMPL_TYPE_MACHINESTATE_H

namespace ara
{
namespace exec
{

enum class MachineState : uint8_t
{
    Off = 0,
    Start = 1,
	Run = 2,
	Update = 3,
	Acc = 4,
	Reset = 5,
	Sleep = 6
};

} // namespace exec
} // namespace ara

#endif // ARA_EXEC_IMPL_TYPE_MACHINESTATE_H

