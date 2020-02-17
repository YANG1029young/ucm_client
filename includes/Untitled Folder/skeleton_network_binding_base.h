/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_BINDING_SKELETON_NETWORK_BINDING_BASE_H_
#define ARA_COM_INTERNAL_BINDING_SKELETON_NETWORK_BINDING_BASE_H_

#include <ara/com/types.h>
#include <ara/com/internal/binding/network_binding_base.h>

#include "marshal.h"

namespace ara
{
namespace com
{
namespace internal
{
namespace binding
{

class SkeletonNetworkBindingBase : public NetworkBindingBase
{
public:
    SkeletonNetworkBindingBase(std::string serviceName, uint16_t instanceId, ara::com::internal::NetWorkBindingType type
        , MessageReceiveHandler handler);
    virtual ~SkeletonNetworkBindingBase();
    
    virtual void offerService() = 0;
    virtual void stopOfferService() = 0;
    
    template <typename Class, typename R, typename... Args, std::size_t... I>
    void HandleCall(Class& c,
        ara::core::Future<R> (Class::*method)(Args...),
        const std::shared_ptr<Message> msg,
        std::index_sequence<I...>
    )
    {
        std::shared_ptr<Deserializer> deserializer = getDeserializer(msg->payload->data(), msg->payload->size());
        Unmarshaller<Args...> unmarshaller(deserializer, msg->payload->data(), msg->payload->size());
        
        if (unmarshaller.hasInvalidArgData())
        {
            logger().LogError() << CODE_POS(__FILE__, __FUNCTION__, __LINE__) << "invalid arg data for method " << msg->methodName;
            sendError(msg, ReturnCode::E_MALFORMED_MESSAGE);
            return;
        }
        
        ara::core::Future<R> f = (c.*method)(unmarshaller.template unmarshal<I>()...);
        
        f.then([this,msg](ara::core::Future<R>&& f)->bool{
            try
            {
                R r = f.get();
                
                std::shared_ptr<Serializer> serializer = getSerializer();
                serializer->Serialize(r);
                
                return sendResponse(msg, serializer->GetPayload());
            }
            catch(ara::com::ApplicationErrorException& e)
            {
                std::shared_ptr<Serializer> serializer = getSerializer();
                static std::shared_ptr<std::vector<uint8_t>> payload = 
                    ara::com::internal::Factory::ErrorSerialize(m_serviceName, e, serializer);
                return sendError(msg, payload);
            }
            catch(std::runtime_error& e)
            {
                return sendError(msg, ReturnCode::E_UNKNOWN_METHOD);
            }
        });
    }
    
    template <typename Class, typename... Args, std::size_t... I>
    void HandleCall(Class& c,
        ara::core::Future<void> (Class::*method)(Args...),
        const std::shared_ptr<Message> msg,
        std::index_sequence<I...>
    )
    {
        std::shared_ptr<Deserializer> deserializer = getDeserializer(msg->payload->data(), msg->payload->size());
        Unmarshaller<Args...> unmarshaller(deserializer, msg->payload->data(), msg->payload->size());
        
        if (unmarshaller.hasInvalidArgData())
        {
            logger().LogError() << CODE_POS(__FILE__, __FUNCTION__, __LINE__) << "invalid arg data for method " << msg->methodName;
            sendError(msg, ReturnCode::E_MALFORMED_MESSAGE);
            return;
        }
        
        ara::core::Future<void> f = (c.*method)(unmarshaller.template unmarshal<I>()...);
      
        f.then([this,msg](ara::core::Future<void>&& f)->bool{
            try
            {
                f.get();
                
                return sendResponse(msg);
            }
            catch(ara::com::ApplicationErrorException& e)
            {
                std::shared_ptr<Serializer> serializer = getSerializer();
                static std::shared_ptr<std::vector<uint8_t>> payload = 
                    ara::com::internal::Factory::ErrorSerialize(m_serviceName, e, serializer);
                return sendError(msg, payload);
            }
            catch(std::runtime_error& e)
            {
                return sendError(msg, ReturnCode::E_UNKNOWN_METHOD);
            }
        });
    }
    
    template <typename Class, typename R>
    void HandleCall(Class& c,
        ara::core::Future<R> (Class::*method)(),
        const std::shared_ptr<Message> msg
    )
    {
        ara::core::Future<R> f = (c.*method)();
        
        f.then([this,msg](ara::core::Future<R>&& f)->bool{
            try
            {
                R r = f.get();
                
                std::shared_ptr<Serializer> serializer = getSerializer();
                serializer->Serialize(r);
                
                return sendResponse(msg, serializer->GetPayload());
            }
            catch(ara::com::ApplicationErrorException& e)
            {
                std::shared_ptr<Serializer> serializer = getSerializer();
                static std::shared_ptr<std::vector<uint8_t>> payload = 
                    ara::com::internal::Factory::ErrorSerialize(m_serviceName, e, serializer);
                return sendError(msg, payload);
            }
            catch(std::runtime_error& e)
            {
                return sendError(msg, ReturnCode::E_UNKNOWN_METHOD);
            }
        });
    }
    
    template <typename Class>
    void HandleCall(Class& c,
        ara::core::Future<void> (Class::*method)(),
        const std::shared_ptr<Message> msg
    )
    {
        ara::core::Future<void> f = (c.*method)();
      
        f.then([this,msg](ara::core::Future<void>&& f)->bool{
            try
            {
                f.get();
                
                return sendResponse(msg);
            }
            catch(ara::com::ApplicationErrorException& e)
            {
                std::shared_ptr<Serializer> serializer = getSerializer();
                static std::shared_ptr<std::vector<uint8_t>> payload = 
                    ara::com::internal::Factory::ErrorSerialize(m_serviceName, e, serializer);
                return sendError(msg, payload);
            }
            catch(std::runtime_error& e)
            {
                return sendError(msg, ReturnCode::E_UNKNOWN_METHOD);
            }
        });
    }
    
    template <typename Class, typename... Args, std::size_t... I>
    void HandleCall(Class& c,
        void (Class::*method)(Args...),
        const std::shared_ptr<Message> msg,
        std::index_sequence<I...>
    )
    {
        std::shared_ptr<Deserializer> deserializer = getDeserializer(msg->payload->data(), msg->payload->size());
        Unmarshaller<Args...> unmarshaller(deserializer, msg->payload->data(), msg->payload->size());
        
        if (unmarshaller.hasInvalidArgData())
        {
            logger().LogError() << CODE_POS(__FILE__, __FUNCTION__, __LINE__) << "invalid arg data for method " << msg->methodName;
            return;
        }
        
        (c.*method)(unmarshaller.template unmarshal<I>()...);
    }
    
    template <typename Class>
    void HandleCall(Class& c,
        void (Class::*method)(),
        const std::shared_ptr<Message> msg
    )
    {
        (c.*method)();
    }
    
    template <typename T>
    void sendEvent(std::string eventName, const T& data, bool is_field)
    {        
        std::shared_ptr<Serializer> serializer = getSerializer();
        serializer->Serialize(data);
        
        sendEvent(eventName, serializer->GetPayload(), is_field);
    }
    
    virtual bool sendError(const std::shared_ptr<Message> msg, ReturnCode code = ReturnCode::E_NOT_OK) = 0;

protected:
    void E2EProtect(std::string name, std::shared_ptr<std::vector<uint8_t>> buffer);
    
    virtual bool sendResponse(const std::shared_ptr<Message> msg, const std::shared_ptr<std::vector<uint8_t>> payload) = 0;
    virtual bool sendResponse(const std::shared_ptr<Message> msg) = 0;
    virtual bool sendError(const std::shared_ptr<Message> msg, const std::shared_ptr<std::vector<uint8_t>> payload) = 0;
    virtual bool sendEvent(std::string eventName, const std::shared_ptr<std::vector<uint8_t>> payload, bool is_field) = 0;
};

} // binding
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_BINDING_SKELETON_NETWORK_BINDING_BASE_H_
