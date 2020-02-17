/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_PROXY_PROXY_BASE_H_
#define ARA_COM_INTERNAL_PROXY_PROXY_BASE_H_

#include <ara/com/types.h>
#include "service_proxy.h"

namespace ara
{
namespace com
{
namespace internal
{
namespace proxy
{

class ProxyBase
{
protected:
    ProxyBase(ServiceProxy* service);
    virtual ~ProxyBase();
    
    void EventSubscribe(std::string name);
    void EventUnsubscribe(std::string name);
    void SetEventReceiveHandler(std::string name, std::function<void(std::shared_ptr<std::vector<uint8_t>>)> handler);
    void UnsetEventReceiveHandler(std::string name);
    void SetEventSubscriptionStateChangeHandler(std::string name, ara::com::SubscriptionStateChangeHandler handler);
    void UnsetEventSubscriptionStateChangeHandler(std::string name);
    const ara::com::e2exf::E2EResult GetE2EResult(std::string name) const;
    
    template <typename T>
    void UpdateEventSample(std::string name,
        ara::com::SampleContainer<ara::com::SamplePtr<const T>>& samples,
        std::vector<std::shared_ptr<std::vector<uint8_t>>> payloads,
        ara::com::FilterFunction<T> filter, size_t cacheSize = 1)
    {
        m_service->UpdateEventSample(name, samples, payloads, filter, cacheSize);
    }
    
    template <typename... Args>
    ara::core::Future<void> SendRequest(std::string name, Args&&... args)
    {
        return m_service->SendRequest(name, std::forward<Args>(args)...);
    }
    
    template <typename R, typename... Args>
    ara::core::Future<R> SendRequest(std::string name, Args&&... args)
    {
        return m_service->SendRequest<R>(name, std::forward<Args>(args)...);
    }
    
    template <typename R>
    ara::core::Future<R> SendRequest(std::string name)
    {
        return m_service->SendRequest<R>(name);
    }
    
    template <typename... Args>
    void SendFireAndForgetRequest(std::string name, Args&&... args)
    {
        m_service->SendFireAndForgetRequest(name, std::forward<Args>(args)...);
    }
    
    void SendFireAndForgetRequest(std::string name)
    {
        m_service->SendFireAndForgetRequest(name);
    }

private:    
    ServiceProxy* m_service;
};

} // proxy
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_PROXY_PROXY_BASE_H_
