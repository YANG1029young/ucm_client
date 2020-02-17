/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_BINDING_IPC_IPC_PROXY_NETWORK_BINDING_H_
#define ARA_COM_INTERNAL_BINDING_IPC_IPC_PROXY_NETWORK_BINDING_H_

#include <ara/com/internal/common.h>
#include <ara/com/internal/binding/proxy_network_binding_base.h>
#include <ara/com/internal/binding/ipc/ipc_network_binding_base.h>

namespace ara
{
namespace com
{
namespace internal
{
namespace binding
{
namespace ipc
{
        
class IpcProxyNetworkBinding : public ara::com::internal::binding::ProxyNetworkBindingBase, public IpcNetworkBindingBase
{
public:
    IpcProxyNetworkBinding(std::string serviceName, uint16_t instanceId, MessageReceiveHandler handler, uint16_t clientId);
    virtual ~IpcProxyNetworkBinding();
    
    static bool FindService(std::string serviceName, uint16_t instanceId, uint16_t& clientId);
    
    static void StartFindService(std::string serviceName, uint16_t instanceId, uint32_t uid, std::function<void(uint16_t)>handler);
    
    static void StopFindService(uint32_t uid);
    
    virtual void init(std::shared_ptr<ServiceInterface> si);
    
    virtual void EventSubscribe(std::string name);
    virtual void EventUnsubscribe(std::string name);
    virtual void SetEventSubscriptionStateChangeHandler(std::string name, ara::com::SubscriptionStateChangeHandler handler);
    virtual void UnsetEventSubscriptionStateChangeHandler(std::string name);
    virtual ara::com::e2exf::E2EResult GetE2EResult(std::string name);

private:
    void startup();
    bool openSocket();

    std::shared_ptr<Serializer> getSerializer() override;
    std::shared_ptr<Deserializer> getDeserializer(const uint8_t *data, uint32_t size) override;
    
    void SendMethodRequest(std::shared_ptr<Message> msg, ResponseReceiveHandler handler);
    
    void OnConnectionState(bool connected);
    
    uint16_t GetSessionId();
    
    void ReSubscribe();

    void createConnectThread(std::string serviceName);
    void createReadThread();
    void createMsgThread();

    void invokeFindHandler();
    
    int m_fd;
    int m_clientid_fd;
    std::string m_path;
    bool m_connected;
    uint16_t m_session;
    std::mutex m_mutexClientId;
    std::mutex m_mutexSession;
    std::mutex m_mutexEventState;
    std::mutex m_mutexConnect;
    std::mutex m_mutexConnected;
    std::condition_variable m_conditionConnect;
    std::condition_variable m_conditionConnected;

    std::map<std::string,bool> m_subscriberEventStatus;
    std::map<std::string,ara::com::SubscriptionStateChangeHandler> m_eventStateHandlers;
    std::vector<std::shared_ptr<ara::core::Promise<void>>> m_thread_joins;
};

} // ipc
} // binding
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_BINDING_IPC_IPC_PROXY_NETWORK_BINDING_H_
