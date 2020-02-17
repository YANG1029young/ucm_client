#ifndef ARA_EXEC_IMPL_TYPE_SETSTATERESPONSESTATUS_H
#define ARA_EXEC_IMPL_TYPE_SETSTATERESPONSESTATUS_H

namespace ara
{
namespace exec
{

enum class SetStateResponseStatus : uint8_t
{
    kSuccess,
    kAccepted,
    kFailed,
    kTimeout,
    kIgnored
};

} // namespace exec
} // namespace ara

#endif // ARA_EXEC_IMPL_TYPE_SETSTATERESPONSESTATUS_H

