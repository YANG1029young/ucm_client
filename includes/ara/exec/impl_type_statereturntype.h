#ifndef ARA_EXEC_IMPL_TYPE_STATERETURNTYPE_H
#define ARA_EXEC_IMPL_TYPE_STATERETURNTYPE_H

namespace ara
{
namespace exec
{

enum class StateReturnType : uint8_t
{
    kSuccess = 0,
    kBusy = 1,
    kGeneralError = 2
};

} // namespace exec
} // namespace ara

#endif // ARA_EXEC_IMPL_TYPE_STATERETURNTYPE_H

