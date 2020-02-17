#ifndef ARA_EXEC_IMPL_TYPE_GETSTATERESPONSESTATUS_H
#define ARA_EXEC_IMPL_TYPE_GETSTATERESPONSESTATUS_H

namespace ara
{
namespace exec
{

enum class GetStateResponseStatus : uint8_t
{
    kSuccess,
    kTransition,
    kStateFailed,
    kTransitionFailed,
    kTimeout,
    kInvalidRequest
};

} // namespace exec
} // namespace ara

#endif // ARA_EXEC_IMPL_TYPE_GETSTATERESPONSESTATUS_H

