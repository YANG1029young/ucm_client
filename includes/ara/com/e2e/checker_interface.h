// --------------------------------------------------------------------------
// |              _    _ _______     .----.      _____         _____        |
// |         /\  | |  | |__   __|  .  ____ .    / ____|  /\   |  __ \       |
// |        /  \ | |  | |  | |    .  / __ \ .  | (___   /  \  | |__) |      |
// |       / /\ \| |  | |  | |   .  / / / / v   \___ \ / /\ \ |  _  /       |
// |      / /__\ \ |__| |  | |   . / /_/ /  .   ____) / /__\ \| | \ \       |
// |     /________\____/   |_|   ^ \____/  .   |_____/________\_|  \_\      |
// |                              . _ _  .                                  |
// --------------------------------------------------------------------------
//
// All Rights Reserved.
// Any use of this source code is subject to a license agreement with the
// AUTOSAR development cooperation.
// More information is available at www.autosar.org.
//
// Disclaimer
//
// This work (specification and/or software implementation) and the material
// contained in it, as released by AUTOSAR, is for the purpose of information
// only. AUTOSAR and the companies that have contributed to it shall not be
// liable for any use of the work.
//
// The material contained in this work is protected by copyright and other
// types of intellectual property rights. The commercial exploitation of the
// material contained in this work requires a license to such intellectual
// property rights.
//
// This work may be utilized or reproduced without any modification, in any
// form or by any means, for informational purposes only. For any other
// purpose, no part of the work may be utilized or reproduced, in any form
// or by any means, without permission in writing from the publisher.
//
// The work has been developed for automotive applications only. It has
// neither been developed, nor tested for non-automotive applications.
//
// The word AUTOSAR and the AUTOSAR logo are registered trademarks.
// --------------------------------------------------------------------------

#ifndef ARA_COM_E2E_CHECKER_INTERFACE_H
#define ARA_COM_E2E_CHECKER_INTERFACE_H

#include <apd/crc/buffer.h>

#include <ara/com/e2e/profile_interface.h>
#include <ara/com/e2e/state_machine.h>

namespace ara
{

namespace com
{

namespace profile
{

/// @brief Profile-independent status of the reception on one single Data in one cycle.
/// @note This enumeration left for compatibility with classic platform
///
/// @uptrace{SWS_E2E_00347}
/// @uptrace{SWS_CM_90421}
enum class ProfileCheckStatus : uint8_t
{
    // clang-format off
    Ok,  ///< OK: The checks of the Data in this cycle were successful
    NoNewData,  ///< Error: The Check function has been invoked but no new Data is not available since the last call, according to communication medium
    Error,  ///< Error: error not related to counters occurred (e.g. wrong CRC, wrong length, wrong options, wrong Data ID)
    Repeated,  ///< Error: the checks of the Data in this cycle were successful, with the exception of the repetition
    OkSomeLost,  ///< OK: the checks of the Data in this cycle were successful (including counter check, which was incremented within the allowed configured delta)
    WrongSequence  ///< Error: the checks of the Data in this cycle were successful, with the exception of counter jump, which changed more than the allowed delta
    // clang-format on
};

/// @brief Converts ProfileCheckStatus type  to CheckStatus type of StateMachine
///
/// @param status profile check status
///
/// @return StateMachine CheckStatus type
inline ara::com::E2E_state_machine::E2ECheckStatus MapProfileCheckStatusToCheckStatus(ProfileCheckStatus status)
{
    switch (status) {
    case ProfileCheckStatus::Ok:
        return com::E2E_state_machine::E2ECheckStatus::Ok;
    case ProfileCheckStatus::OkSomeLost:
        return com::E2E_state_machine::E2ECheckStatus::Ok;
    case ProfileCheckStatus::Error:
        return com::E2E_state_machine::E2ECheckStatus::Error;
    case ProfileCheckStatus::Repeated:
        return com::E2E_state_machine::E2ECheckStatus::Repeated;
    case ProfileCheckStatus::WrongSequence:
        return com::E2E_state_machine::E2ECheckStatus::WrongSequence;
    case ProfileCheckStatus::NoNewData:
        return com::E2E_state_machine::E2ECheckStatus::NoNewData;
    };
    // FIXME functions that use this were declared noexcept
    return com::E2E_state_machine::E2ECheckStatus::Error;
}

namespace profile_interface
{

/// @brief Interface of E2E checker.
///
/// E2E performs check routine on given data.
class CheckerInterface : public ProfileInterface
{
public:
    /// @brief Default destructor
    ~CheckerInterface() noexcept override = default;

    /// @brief Check routine performs validation of E2E header that is supplied within other data in buffer parameter
    ///
    /// @param buffer                     buffer with payload and E2E header
    /// @param genericProfileCheckStatus  Result of check routine
    virtual void Check(const apd::crc::Buffer& buffer,
        com::E2E_state_machine::E2ECheckStatus& genericProfileCheckStatus) noexcept
        = 0;
        
    virtual void Reset() noexcept = 0;
};

}  // namespace profile_interface
}  // namespace profile
}  // namespace com
}  // namespace ara

#endif  // ARA_COM_E2E_CHECKER_INTERFACE_H
