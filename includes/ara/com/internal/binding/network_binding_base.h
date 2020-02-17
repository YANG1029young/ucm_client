/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_BINDING_NETWORK_BINDING_BASE_H_
#define ARA_COM_INTERNAL_BINDING_NETWORK_BINDING_BASE_H_

#include <ara/com/types.h>
#include <ara/com/internal/manifest.h>

#include <ara/com/e2e/checker_interface.h>
#include <ara/com/e2e/protector_interface.h>
#include <ara/com/e2e/state_machine.h>

namespace ara
{
namespace com
{
namespace internal
{
namespace binding
{

class NetworkBindingBase
{
public:
    NetworkBindingBase(std::string serviceName, uint16_t instanceId, ara::com::internal::NetWorkBindingType type, MessageReceiveHandler handler);
    virtual ~NetworkBindingBase();
    
    ara::com::internal::NetWorkBindingType GetType() const;
    
    void onMessage(const std::shared_ptr<Message> msg);
    
    virtual void init(std::shared_ptr<ServiceInterface> si) = 0;
    virtual std::shared_ptr<Serializer> getSerializer() = 0;
    virtual std::shared_ptr<Deserializer> getDeserializer(const uint8_t *data, uint32_t size) = 0;
    
protected:
    std::string m_serviceName;
    uint16_t m_instanceId;
    ara::com::internal::NetWorkBindingType m_type;
    MessageReceiveHandler m_handler;
    std::mutex m_mutexHandler;
    uint16_t m_clientId;
    std::map<std::string,std::shared_ptr<End2EndEventProtectionProps>> m_e2eEventProtectionProps;
    std::map<uint32_t,std::shared_ptr<ara::com::profile::profile_interface::ProtectorInterface>> m_profileProtectors;
    std::map<uint32_t,std::shared_ptr<ara::com::profile::profile_interface::CheckerInterface>> m_profileCheckers;
    std::map<uint32_t,std::shared_ptr<ara::com::E2E_state_machine::StateMachine>> m_stateMachines;
    
    void loadE2EEventProtectionProps(std::vector<std::shared_ptr<End2EndEventProtectionProps>> e2eEventProtectionProps);
    bool isE2EEnabled(std::string name);
    
    void copyMessage(const std::shared_ptr<Message> dst, const std::shared_ptr<Message> src, ara::com::internal::MessageType type, ara::com::internal::ReturnCode code);
};

} // binding
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_BINDING_PROXY_NETWORK_BINDING_BASE_H_
