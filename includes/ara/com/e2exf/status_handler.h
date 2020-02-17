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

#ifndef ARA_COM_E2EXF_STATUS_HANDLER_H
#define ARA_COM_E2EXF_STATUS_HANDLER_H

#include <cstdint>
#include <string>

#include <ara/com/e2e/state_machine.h>
#include <ara/com/e2exf/types.h>

namespace ara
{
namespace com
{
namespace e2exf
{

class StatusHandler {
public:
    static bool Configure(const std::string& bindingConfigurationPath,
        ConfigurationFormat bindingConfigurationFormat,
        const std::string& e2exfConfigurationPath,
        ConfigurationFormat e2exfConfigurationFormat);

    static E2EResult HandleCheckStatus(std::uint16_t serviceId,
        std::uint16_t instanceId,
        std::uint16_t eventId,
        ara::com::E2E_state_machine::E2ECheckStatus checkStatus);
};

}  // namespace e2exf
}  // namespace com
}  // namespace ara

#endif  // ARA_COM_E2EXF_STATUS_HANDLER_H
