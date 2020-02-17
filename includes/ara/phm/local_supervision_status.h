#ifndef ARA_PHM_LOCAL_SUPERVISION_STATUS_H_
#define ARA_PHM_LOCAL_SUPERVISION_STATUS_H_

#include <cstdint>

namespace ara
{
namespace phm
{

/// @brief Enumeration of local supervision status.
///
/// @uptrace{SWS_PHM_01136}
enum class LocalSupervisionStatus : uint8_t
{
    DEINIT,
    DEACTIVATED,
    OK,
    FAILED,
    EXPIRED
};

}  // namespace phm
}  // namespace ara

#endif  // ARA_PHM_LOCAL_SUPERVISION_STATUS_H_
