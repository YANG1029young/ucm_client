/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_BINDING_SOMEIP_SOMEIP_PROXY_NETWORK_BINDING_H_
#define ARA_COM_INTERNAL_BINDING_SOMEIP_SOMEIP_PROXY_NETWORK_BINDING_H_

#include <ara/com/internal/binding/proxy_network_binding_base.h>
#include "someip_network_binding_base.h"

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

class SomeipProxyNetworkBinding : public ara::com::internal::binding::ProxyNetworkBindingBase, public SomeipNetworkBindingBase
{
public:
    SomeipProxyNetworkBinding(std::string serviceName, uint16_t instanceId, MessageReceiveHandler handler, uint16_t findId);
    virtual ~SomeipProxyNetworkBinding();
    
    static bool FindService(std::string serviceName, uint16_t instanceId, uint16_t& uint16_t);
    
    static uint16_t StartFindService(std::string serviceName, uint16_t instanceId, uint32_t uid, std::function<void(uint16_t)>handler);
    
    static void StopFindService(uint32_t uid);
    
    virtual void init(std::shared_ptr<ServiceInterface> si);
    
    virtual void EventSubscribe(std::string name);
    virtual void EventUnsubscribe(std::string name);
    virtual void SetEventSubscriptionStateChangeHandler(std::string name, ara::com::SubscriptionStateChangeHandler handler);
    virtual void UnsetEventSubscriptionStateChangeHandler(std::string name);
    virtual ara::com::e2exf::E2EResult GetE2EResult(std::string name);
    
private:
    std::shared_ptr<Serializer> getSerializer() override;
    std::shared_ptr<Deserializer> getDeserializer(const uint8_t *data, uint32_t size) override;
    
    void SendMethodRequest(std::shared_ptr<Message> msg, ResponseReceiveHandler handler);
    
    uint16_t GetSessionId();
    
    void OnAvailable(bool available);
    
    uint16_t m_session;
    uint16_t m_findId;
    std::mutex m_mutexSession;
    
    std::mutex m_mutexEventState;
    std::map<uint16_t,bool> m_subscriberEventStatus;
    std::map<std::string,ara::com::SubscriptionStateChangeHandler> m_eventStateHandlers;
    std::shared_ptr<ApSomeipTransformationProps> m_transformationProps;
};

} // someip
} // binding
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_BINDING_SOMEIP_SOMEIP_PROXY_NETWORK_BINDING_H_
