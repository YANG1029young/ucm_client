#ifndef ARA_PHM_GLOBAL_SUPERVISION_STATUS_H_
#define ARA_PHM_GLOBAL_SUPERVISION_STATUS_H_

#include <cstdint>

namespace ara
{
namespace phm
{

/// @brief Enumeration of global supervision status.
///
/// @uptrace{SWS_PHM_01137}
enum class GlobalSupervisionStatus : uint8_t
{
    DEINIT,
    DEACTIVATED,
    OK,
    FAILED,
    EXPIRED,
    STOPPED
};

}  // namespace phm
}  // namespace ara

#endif  // ARA_PHM_GLOBAL_SUPERVISION_STATUS_H_
