/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_PROXY_EVENT_BASE_H_
#define ARA_COM_INTERNAL_PROXY_EVENT_BASE_H_

#include <ara/com/types.h>
#include <ara/com/e2exf/types.h>
#include "proxy_base.h"

namespace ara
{
namespace com
{
namespace internal
{
namespace proxy
{

class EventBase : protected ProxyBase
{
public:
    EventBase(ServiceProxy* service, std::string name);
    
    virtual ~EventBase();
    
    void Subscribe(ara::com::EventCacheUpdatePolicy policy, size_t cacheSize);
    
    void Unsubscribe();
    
    ara::com::SubscriptionState GetSubscriptionState() const;
    
    void SetReceiveHandler(ara::com::EventReceiveHandler handler);
    
    void UnsetReceiveHandler();
    
    void SetSubscriptionStateChangeHandler(ara::com::SubscriptionStateChangeHandler handler);
    
    void UnsetSubscriptionStateChangeHandler();
    
    void Cleanup();
    
    const ara::com::e2exf::E2EResult GetE2EResult() const;

protected:
    std::string m_name;
    EventCacheUpdatePolicy m_policy;
    size_t m_cacheSize;
    std::vector<std::shared_ptr<std::vector<uint8_t>>> m_data;
    EventReceiveHandler m_handler;
    SubscriptionStateChangeHandler m_stateHandler;
    SubscriptionState m_state;
    std::mutex m_mutex;
};

} // proxy
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_PROXY_EVENT_BASE_H_
