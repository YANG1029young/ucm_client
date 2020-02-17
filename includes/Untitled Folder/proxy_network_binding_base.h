/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_BINDING_PROXY_NETWORK_BINDING_BASE_H_
#define ARA_COM_INTERNAL_BINDING_PROXY_NETWORK_BINDING_BASE_H_

#include <ara/com/types.h>
#include <ara/com/internal/binding/network_binding_base.h>
#include <ara/core/error_code.h>
#include <ara/com/e2exf/types.h>

#include <map>

namespace ara
{
namespace com
{
namespace internal
{
namespace binding
{


enum class method_errc : int32_t
{
    E_OK = 0x00,
    E_NOT_OK = 0x01,
    E_UNKNOWN_SERVICE = 0x02,
    E_UNKNOWN_METHOD = 0x03,
    E_NOT_READY = 0x04,
    E_NOT_REACHABLE = 0x05,
    E_TIMEOUT = 0x06,
    E_WRONG_PROTOCOL_VERSION = 0x07,
    E_WRONG_INTERFACE_VERSION = 0x08,
    E_MALFORMED_MESSAGE = 0x09,
    E_WRONG_MESSAGE_TYPE = 0xA,
    E_UNKNOWN = 0xFF
};

class MethodException : public ara::core::Exception
{
public:
    /**
     * @brief Construct a new future exception object containing an Error object.
     */
    explicit MethodException(ara::core::ErrorCode&& err) noexcept
        : ara::core::Exception(std::move(err))
    {
    }
};

class MethodErrorDomain : public ara::core::ErrorDomain
{
    constexpr static ErrorDomain::IdType kId = 0x029f881224e61118LL;

public:
    using Errc = method_errc;
    using Exception = MethodException;

    constexpr MethodErrorDomain() noexcept
        : ara::core::ErrorDomain(kId)
    {
    }

    char const* Name() const noexcept override
    {
        return "MethodError";
    }

    char const* Message(ara::core::ErrorDomain::CodeType errorCode) const noexcept override
    {
        Errc const code = static_cast<Errc>(errorCode);
        switch (code) {
        case Errc::E_OK:
            return "OK";
        case Errc::E_NOT_OK:
            return "NOT OK";
        case Errc::E_UNKNOWN_SERVICE:
            return "UNKNOWN SERVICE";
        case Errc::E_UNKNOWN_METHOD:
            return "UNKNOWN METHOD";
        case Errc::E_NOT_READY:
            return "NOT READY";
        case Errc::E_NOT_REACHABLE:
            return "NOT REACHABLE";
        case Errc::E_TIMEOUT:
            return "TIMEOUT";
        case Errc::E_WRONG_PROTOCOL_VERSION:
            return "WRONG PROTOCOL VERSION";
        case Errc::E_WRONG_INTERFACE_VERSION:
            return "WRONG INTERFACE VERSION";
        case Errc::E_MALFORMED_MESSAGE:
            return "MALFORMED MESSAGE";
        case Errc::E_WRONG_MESSAGE_TYPE:
            return "WRONG MESSAGE TYPE";
        case Errc::E_UNKNOWN:
            return "UNKNOWN";
        default:
            return "UNKNOWN METHOD ERROR";
        }
    }

    void ThrowAsException(ara::core::ErrorCode const& errorCode) const noexcept(false) override
    {
        ara::core::ThrowOrTerminate<ara::core::Exception>(errorCode);
    }
};

namespace internal
{
    constexpr MethodErrorDomain g_methodErrorDomain;
}

inline constexpr ara::core::ErrorDomain const& GetMethodDomain()
{
    return internal::g_methodErrorDomain;
}

using ResponseReceiveHandler = std::function<void (std::shared_ptr<Message>)>;

class ProxyNetworkBindingBase : public NetworkBindingBase
{    
public:

    using E2EState = com::E2E_state_machine::E2EState;
    using E2ECheckStatus = com::E2E_state_machine::E2ECheckStatus;
    using E2EResult = ara::com::e2exf::E2EResult;
    
    ProxyNetworkBindingBase(std::string serviceName, uint16_t instanceId, ara::com::internal::NetWorkBindingType type
        , MessageReceiveHandler handler);
    virtual ~ProxyNetworkBindingBase();
    
    virtual void EventSubscribe(std::string name) = 0;
    virtual void EventUnsubscribe(std::string name) = 0;
    virtual void SetEventSubscriptionStateChangeHandler(std::string name, ara::com::SubscriptionStateChangeHandler handler) = 0;
    virtual void UnsetEventSubscriptionStateChangeHandler(std::string name) = 0;
    virtual ara::com::e2exf::E2EResult GetE2EResult(std::string name) = 0;
    
    template <typename... Args>
    ara::core::Future<void> SendRequest(std::string name, Args&&... args)
    {
        std::shared_ptr<ara::core::Promise<void>> promise = std::make_shared<ara::core::Promise<void>>();
        
        ara::core::Future<void> future = promise->get_future();
        
        std::shared_ptr<Serializer> serializer = getSerializer();
        Serialize(serializer, args...);
        
        std::shared_ptr<Message> msg = std::make_shared<Message>();
        msg->type = MessageType::MT_REQUEST;
        msg->payload = serializer->GetPayload();
        msg->methodName = name;
        
        SendMethodRequest(msg, [this, promise, name](std::shared_ptr<Message> msg){
            if (msg->code == ara::com::internal::ReturnCode::E_OK)
            {
                promise->set_value();
            }
            else if (msg->code == ara::com::internal::ReturnCode::E_NOT_OK && msg->type == MessageType::MT_ERROR && msg->payload->size() > 0)
            {
                HandlerSetException(promise, name, msg);
            }
            else
            {
                HandlerSetError(promise, name, static_cast<ara::core::ErrorDomain::CodeType>(msg->code));
            }
        });
        
        return future;
    }
    
    template <typename R, typename... Args>
    ara::core::Future<R> SendRequest(std::string name, Args&&... args)
    {
        std::shared_ptr<ara::core::Promise<R>> promise = std::make_shared<ara::core::Promise<R>>();
        
        ara::core::Future<R> future = promise->get_future();
        
        std::shared_ptr<Serializer> serializer = getSerializer();
        Serialize(serializer, args...);
        
        std::shared_ptr<Message> msg = std::make_shared<Message>();
        
        msg->type = MessageType::MT_REQUEST;
        msg->payload = serializer->GetPayload();
        msg->methodName = name;
        
        SendMethodRequest(msg, [this, promise, name](std::shared_ptr<Message> msg){
            if (msg->code == ara::com::internal::ReturnCode::E_OK)
            {
                if (msg->payload->size() > 0)
                {
                    R output;
                    
                    std::shared_ptr<Deserializer> deserializer = getDeserializer(msg->payload->data(), msg->payload->size());
                    
                    if (deserializer->Deserialize(output))
                    {
                        promise->set_value(output);
                    }
                    else
                    {
                        HandlerSetError(promise, name, static_cast<ara::core::ErrorDomain::CodeType>(ReturnCode::E_MALFORMED_MESSAGE));
                    }
                }
                else
                {
                    HandlerSetError(promise, name, static_cast<ara::core::ErrorDomain::CodeType>(msg->code));
                }
            }
            else if (msg->code == ara::com::internal::ReturnCode::E_NOT_OK && msg->type == MessageType::MT_ERROR && msg->payload->size() > 0)
            {
                HandlerSetException(promise, name, msg);
            }
            else
            {
                HandlerSetError(promise, name, static_cast<ara::core::ErrorDomain::CodeType>(msg->code));
            }
        });
        
        return future;
    }
    
    template <typename... Args>
    void SendFireAndForgetRequest(std::string name, Args&&... args)
    {
        std::shared_ptr<Serializer> serializer = getSerializer();
        Serialize(serializer, args...);
        
        std::shared_ptr<Message> msg = std::make_shared<Message>();
        
        msg->type = MessageType::MT_REQUEST_NO_RETURN;
        msg->payload = serializer->GetPayload();
        msg->methodName = name;
        
        std::shared_ptr<ara::core::Promise<void>> promise = std::make_shared<ara::core::Promise<void>>();
        ara::core::Future<void> future = promise->get_future();
        
        SendMethodRequest(msg, [this, promise, name](std::shared_ptr<Message> msg){
            if (msg->code != ara::com::internal::ReturnCode::E_OK)
            {    
                HandlerSetError(promise, name, static_cast<ara::core::ErrorDomain::CodeType>(msg->code));            
            }
            else
            {
                promise->set_value();
            }
        });
        
        future.get();
    }
    
    template <typename T>
    void UpdateEventSample(std::string name,
        ara::com::SampleContainer<ara::com::SamplePtr<const T>>& samples,
        std::vector<std::shared_ptr<std::vector<uint8_t>>> payloads,
        ara::com::FilterFunction<T> filter, size_t cacheSize = 1)
    {
        for (auto payload : payloads)
        {
            const uint8_t *deserializerData = payload->data();
            uint32_t deserializerSize = payload->size();
            T sample;
            
            if (isE2EEnabled(name))
            {
                uint32_t e2eLength = E2ECheck(name, payload);
                
                if (!GetE2EResult(name).IsOK())
                {
                    continue;
                }
                
                deserializerData += e2eLength;
                deserializerSize -= e2eLength;
            }
            
            std::shared_ptr<Deserializer> deserializer = getDeserializer(deserializerData, deserializerSize);
            if (!deserializer->Deserialize(sample))
            {
                logger().LogError() << CODE_POS(__FILE__, __FUNCTION__, __LINE__) << "eventName=" + name + ", Deserialize sample failed";
                continue;
            }
            
            if (filter)
            {
                if (filter(sample))
                {
                    ara::com::SamplePtr<const T> ptr = make_sample_ptr<const T>(sample);
                    samples.push_back(ptr);
                    
                    if (samples.size() > cacheSize)
                    {
                        samples.erase(samples.begin());
                    }
                }
            }
            else
            {
                ara::com::SamplePtr<const T> ptr = make_sample_ptr<const T>(sample);
                samples.push_back(ptr);
                
                if (samples.size() > cacheSize)
                {
                    samples.erase(samples.begin());
                }
            }
        }
    }
    
protected:
    virtual void SendMethodRequest(std::shared_ptr<Message> msg, ResponseReceiveHandler handler) = 0;
    
    void AddHandler(uint32_t request, ResponseReceiveHandler handler);
    void InvokeHandler(uint32_t request, std::shared_ptr<Message> msg);
    void ClearHandler();
    uint32_t E2ECheck(std::string name, std::shared_ptr<std::vector<uint8_t>> buffer);
    void resetChecker(std::string name);
    
    std::map<uint32_t,ResponseReceiveHandler> m_handlers;
    std::mutex m_mutexHandlers;
    
    std::map<std::string,E2EResult> m_e2EResults;

private:
    template <typename T>
    void Serialize(std::shared_ptr<Serializer> serializer, const T& value)
    {
        serializer->Serialize(value);
    }
    
    template <typename T, typename... Args>
    void Serialize(std::shared_ptr<Serializer> serializer, const T& value, Args&&... args)
    {
        serializer->Serialize(value);
        Serialize(serializer, args...);
    }
    
    void Serialize(std::shared_ptr<Serializer> serializer);
    
    template <typename P>
    void HandlerSetError(P promise, std::string methodName, ara::core::ErrorDomain::CodeType code)
    {
        ara::core::ErrorCode errc(code, GetMethodDomain(), 0, GetMethodDomain().Message(code));
        promise->SetError(errc);
        logger().LogError() << CODE_POS(__FILE__, __FUNCTION__, __LINE__) << "method=" + methodName + ", return is E_NOT_OK";
    }
    
    template <typename P>
    void HandlerSetException(P promise, std::string methodName, std::shared_ptr<Message> msg)
    {
        std::shared_ptr<Deserializer> deserializer = getDeserializer(msg->payload->data(), msg->payload->size());
        promise->set_exception(Factory::ErrorDeserialize(m_serviceName, msg->payload->at(0), deserializer));
        logger().LogError() << CODE_POS(__FILE__, __FUNCTION__, __LINE__) << "method=" + methodName + ", return is E_NOT_OK";
    }
};

} // binding
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_BINDING_PROXY_NETWORK_BINDING_BASE_H_
