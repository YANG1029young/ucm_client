/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_BINDING_SOMEIP_SOMEIP_NETWORK_BINDING_BASE_H_
#define ARA_COM_INTERNAL_BINDING_SOMEIP_SOMEIP_NETWORK_BINDING_BASE_H_

#include <memory>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <string.h>
#include <map>

#include <ara/com/internal/definitions.h>
#include <ara/com/internal/manifest.h>

#if defined(__linux__)
#include <endian.h>
#elif defined(__QNXNTO__)
#include <net/netbyte.h>
#endif 

namespace ara
{
namespace com
{
namespace internal
{
namespace binding
{
namespace someip
{
        
class SomeipNetworkBindingBase
{
public:
    SomeipNetworkBindingBase();
    virtual ~SomeipNetworkBindingBase();
    
    static void* GetApp();
    static uint16_t GetClientId();

protected:
    void init(std::shared_ptr<ServiceInterface> si);

    std::map<std::string, std::shared_ptr<SomeipMethodDeployment>> m_methods;
    std::map<uint16_t, std::string> m_methodNames;
    std::map<std::string, std::shared_ptr<SomeipEventDeployment>> m_events;
    std::map<uint16_t, std::string> m_eventNames;
    std::map<uint16_t,std::vector<uint16_t>> m_eventgroups;
    std::shared_ptr<ServiceInterface> m_serviceInterface;
    
    std::shared_ptr<SomeipServiceInterfaceDeployment> m_deployment;
};

} // someip
} // binding
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_BINDING_SOMEIP_SOMEIP_NETWORK_BINDING_BASE_H_
