/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_BINDING_IPC_IPC_SKELETON_NETWORK_BINDING_H_
#define ARA_COM_INTERNAL_BINDING_IPC_IPC_SKELETON_NETWORK_BINDING_H_

#include <ara/com/internal/binding/skeleton_network_binding_base.h>
#include <ara/com/internal/binding/marshal.h>

#include "ipc_network_binding_base.h"

#include <utility>
#include <map>

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

class IpcSkeletonNetworkBinding : public ara::com::internal::binding::SkeletonNetworkBindingBase, public IpcNetworkBindingBase
{
public:
    IpcSkeletonNetworkBinding(std::string serviceName, uint16_t instanceId, MessageReceiveHandler handler);
    virtual ~IpcSkeletonNetworkBinding();
    
    virtual void offerService();
    virtual void stopOfferService();
    virtual void init(std::shared_ptr<ServiceInterface> si);
    
private:
    void startup();
    bool openSocket();
    void closeSocket();
    bool addClient(uint16_t clientId, int fd);
    bool delClient(uint16_t clientId, int fd);
    bool sendResponse(const std::shared_ptr<Message> msg, const std::shared_ptr<std::vector<uint8_t>> payload);
    bool sendResponse(const std::shared_ptr<Message> msg);
    bool sendError(const std::shared_ptr<Message> msg, ReturnCode code = ReturnCode::E_NOT_OK);
    bool sendError(const std::shared_ptr<Message> msg, const std::shared_ptr<std::vector<uint8_t>> payload);
    bool sendEvent(std::string eventName, const std::shared_ptr<std::vector<uint8_t>> payload, bool is_field);
    bool sendSubscribeACK(const std::shared_ptr<Message> msg);
    
    std::shared_ptr<Serializer> getSerializer() override;
    std::shared_ptr<Deserializer> getDeserializer(const uint8_t *data, uint32_t size) override;

    void createAcceptThread();
    void createRecvThread();
    void createMsgThread();
    
    int m_fd;
    int m_offer_fd;
    bool m_offer;
    std::string m_path;
    std::mutex m_mutexSocket;
    std::mutex m_mutexOffer;
    std::mutex m_mutexActive;
    std::mutex m_mutexEvent;
    std::condition_variable m_conditionOffer;
    std::condition_variable m_conditionActive;
    
    std::map<uint16_t,int> m_client_fds;
    std::map<uint16_t,std::shared_ptr<ipc_message_state>> m_client_msg_states;
    std::map<uint16_t,std::map<std::string,bool>> m_subscriberEventStatus;
    std::map<std::string,std::shared_ptr<ipc_message>> m_eventMessages;
    std::vector<std::shared_ptr<ara::core::Promise<void>>> m_thread_joins;
};

} // ipc
} // binding
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_BINDING_IPC_IPC_SKELETON_NETWORK_BINDING_H_
