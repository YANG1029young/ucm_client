/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_BINDING_IPC_IPC_NETWORK_BINDING_BASE_H_
#define ARA_COM_INTERNAL_BINDING_IPC_IPC_NETWORK_BINDING_BASE_H_

#include <memory>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <string.h>
#include <map>

#include <ara/com/internal/definitions.h>
#include <ara/com/internal/manifest.h>

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

struct ipc_message
{
    ipc_message()
    :len(0)
    {}
    
    uint32_t len;
    std::vector<uint8_t> data;
};

enum class IPC_STATE: uint8_t
{
    START,
    RECEIVING,
    END
};

struct ipc_message_state
{
    ipc_message_state(IPC_STATE state, int read_len)
    : m_state(state), m_read_len(0)
    {
    }
    
    IPC_STATE m_state;
    unsigned int m_read_len;
    std::shared_ptr<ipc_message> m_msg; 
};
        
class IpcNetworkBindingBase
{
public:
    IpcNetworkBindingBase();
    virtual ~IpcNetworkBindingBase();
    
    bool isTerminated();
    
protected:
    void parse(std::shared_ptr<ipc_message_state> state, const unsigned char *buf, unsigned int len);
    bool send(int fd, std::shared_ptr<ipc_message> ipc_msg);
    void init(std::shared_ptr<ServiceInterface> si);
    
    std::shared_ptr<ipc_message> buildMessage(std::shared_ptr<ara::com::internal::Message> msg);
    std::shared_ptr<ara::com::internal::Message> parseMessage(std::shared_ptr<ipc_message> ipc_msg);
    
    bool m_terminated;
    std::vector<std::shared_ptr<ipc_message>> m_msgs;
    std::mutex m_mutex;
    std::mutex m_mutexMsg;
    std::condition_variable m_conditionMsg;
    std::shared_ptr<ServiceInterface> m_serviceInterface;
    
    static std::map<std::string, bool> m_offeredServices;
};

} // ipc
} // binding
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_BINDING_IPC_IPC_NETWORK_BINDING_BASE_H_
