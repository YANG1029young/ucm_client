#ifndef ARA_PHM_HEALTH_CHANNEL_H_
#define ARA_PHM_HEALTH_CHANNEL_H_

#include <cstdint>
#include <iostream>
#include <type_traits>

#include "ara/phm/phm.h"

namespace ara
{
namespace phm
{

template <typename T>
class HealthChannel
{
    static_assert(DependentFalse<T>::value, "HealthChannel must be created using Identifier template");
};

/// @brief   HealthChannel Class Template
///
/// @uptrace{SWS_PHM_01122}
template <InterfaceType InterfaceId, PrototypeType PrototypeId, typename Enum>
class HealthChannel<Identifier<InterfaceId, PrototypeId, Enum>> : private PHM
{
public:
    /// @brief   Creation of a HealthChannel
    ///
    /// @uptrace{SWS_PHM_00457}
    explicit HealthChannel(PHM const& phm)
        : PHM{phm}
    {}

    /// @brief   ReportHealthStatus method declaration
    ///
    /// @uptrace{SWS_PHM_01128}
    bool ReportHealthStatus(Enum t);
};

/// @brief   ReportHealthStatus method definition
///
/// @uptrace{SWS_PHM_01128}
template <InterfaceType InterfaceId, PrototypeType PrototypeId, typename Enum>
bool HealthChannel<Identifier<InterfaceId, PrototypeId, Enum>>::ReportHealthStatus(Enum t)
{
    auto healthStatusId = static_cast<typename std::underlying_type<Enum>::type>(t);

    return PHM::ReportHealthStatus(InterfaceId, PrototypeId, GetInstanceId(), healthStatusId);
}

}  // namespace phm
}  // namespace ara

#endif  // ARA_PHM_HEALTH_CHANNEL_H_
