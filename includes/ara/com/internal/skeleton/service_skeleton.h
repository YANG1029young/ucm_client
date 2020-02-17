/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_SKELETON_SERVICE_SKELETON_H_
#define ARA_COM_INTERNAL_SKELETON_SERVICE_SKELETON_H_

#include <ara/com/types.h>
#include <ara/com/internal/service_base.h>
#include <ara/com/internal/definitions.h>
#include <ara/com/internal/binding/skeleton_network_binding_base.h>

#include <map>
#include <queue>

namespace ara
{
namespace com
{
namespace internal
{
namespace skeleton
{

class SkeletonBase;

class ServiceSkeleton : public ara::com::internal::ServiceBase
{
public:
    using binding_base_type = ara::com::internal::binding::SkeletonNetworkBindingBase;

    ServiceSkeleton(
        std::string name,
        ara::com::InstanceIdentifier instance,
        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent
    );
    
    virtual ~ServiceSkeleton();
    
    void OfferService();
    
    void StopOfferService();
    
    ara::core::Future<bool> ProcessNextMethodCall();
    
protected:
    void init();
    virtual void DispatchMethodCall(const std::shared_ptr<Message> msg, std::shared_ptr<binding_base_type> binding) = 0;
    
    template <typename Class, typename R, typename... Args>
    void HandleCall(Class& c,
        ara::core::Future<R> (Class::*method)(Args...),
        const std::shared_ptr<Message> msg,
        std::shared_ptr<binding_base_type> binding
    )
    {
        binding->HandleCall(c, method, msg, std::index_sequence_for<Args...>());
    }
    
    template <typename Class, typename... Args>
    void HandleCall(Class& c,
        ara::core::Future<void> (Class::*method)(Args...),
        const std::shared_ptr<Message> msg,
        std::shared_ptr<binding_base_type> binding
    )
    {
        binding->HandleCall(c, method, msg, std::index_sequence_for<Args...>());
    }
    
    template <typename Class, typename R>
    void HandleCall(Class& c,
        ara::core::Future<R> (Class::*method)(),
        const std::shared_ptr<Message> msg,
        std::shared_ptr<binding_base_type> binding
    )
    {
        binding->HandleCall(c, method, msg);
    }
    
    template <typename Class>
    void HandleCall(Class& c,
        ara::core::Future<void> (Class::*method)(),
        const std::shared_ptr<Message> msg,
        std::shared_ptr<binding_base_type> binding
    )
    {
        binding->HandleCall(c, method, msg);
    }
    
    template <typename Class, typename... Args>
    void HandleCall(Class& c,
        void (Class::*method)(Args...),
        const std::shared_ptr<Message> msg,
        std::shared_ptr<binding_base_type> binding
    )
    {
        binding->HandleCall(c, method, msg, std::index_sequence_for<Args...>());
    }
    
    template <typename Class>
    void HandleCall(Class& c,
        void (Class::*method)(),
        const std::shared_ptr<Message> msg,
        std::shared_ptr<binding_base_type> binding
    )
    {
        binding->HandleCall(c, method, msg);
    }
    
    template <typename T>
    ara::core::Future<T> NoHandler()
    {
        ara::core::Promise<T> p;
        try
        {
            // code that may throw
            throw std::runtime_error("Field No Handler");
        }
        catch(...)
        {
            try
            {
                // store anything thrown in the promise
                p.set_exception(std::current_exception());
            }
            catch(...) {} // set_exception() may throw too
        }

        return p.get_future();
    }

private:   
    template <typename T>
    void SendEvent(std::string eventName, const T& data, bool is_field)
    {
        for (auto binding : m_bindings)
        {
            binding.second->sendEvent<T>(eventName, data, is_field);
        }
    }
    
    bool HasRequest();
            
    void ProcessRequest();

    int m_fd;
    ara::com::MethodCallProcessingMode m_mode;
    bool m_terminated;
    std::map<ara::com::internal::NetWorkBindingType, std::shared_ptr<binding_base_type>> m_bindings;
    std::queue<std::shared_ptr<Message>> m_requestMessages;
    std::mutex m_mutex;
    std::condition_variable m_condition;
    std::vector<std::shared_ptr<ara::core::Promise<void>>> m_thread_joins;
    
    friend SkeletonBase;
};

} // skeleton
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_SKELETON_SERVICE_SKELETON_H_

