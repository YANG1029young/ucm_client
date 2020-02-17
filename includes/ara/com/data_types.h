/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_DATA_TYPES_H_
#define ARA_COM_DATA_TYPES_H_

#include "internal/definitions.h"

#include <ara/core/future.h>
#include <ara/core/promise.h>

#include <ara/com/sample_ptr.h>

#include <algorithm>
#include <sstream>
#include <vector>
#include <functional>
#include <memory>
#include <iostream>

namespace ara
{
namespace com
{

class ServiceIdentifierType
{
public:
    explicit ServiceIdentifierType(std::string name)
        :m_name(name)
    {
    }
    
    bool operator==(const ServiceIdentifierType& other) const
    {
        return m_name == other.m_name;
    }
    
    bool operator<(const ServiceIdentifierType& other) const
    {
        return m_name < other.m_name;
    }
    
    ServiceIdentifierType& operator=(const ServiceIdentifierType& other)
    {
        m_name = other.m_name;
        return *this;
    }
    
    std::string toString() const
    {
        return m_name;
    }
    
private:
    std::string m_name;    
};

class ServiceVersionType
{
public:
    constexpr ServiceVersionType(uint8_t majorVersion, uint16_t minorVersion)
        :m_majorVersion(majorVersion), m_minorVersion(minorVersion)
    {
    }
    
    bool operator==(const ServiceVersionType& other) const
    {
        return m_majorVersion == other.m_majorVersion && m_minorVersion == other.m_minorVersion;
    }
    
    bool operator<(const ServiceVersionType& other) const
    {
        return ((m_majorVersion << 16) | m_minorVersion) < ((other.m_majorVersion << 16) | other.m_minorVersion);
    }
    
    ServiceVersionType& operator=(const ServiceVersionType& other)
    {
        m_majorVersion = other.m_majorVersion;
        m_minorVersion = other.m_minorVersion;
        
        return *this;
    }
    
    std::string toString() const
    {
        std::stringstream ss;
        ss << (int)m_majorVersion << "." << (int)m_minorVersion;
        
        return ss.str();
    }

private:
    uint8_t m_majorVersion;
    uint16_t m_minorVersion;
};

class InstanceIdentifier
{
public:
    constexpr InstanceIdentifier(const ara::com::internal::InstanceId id)
        : m_instance_id(id)
    {
    }
    
    explicit InstanceIdentifier(std::string value);
    
    virtual ~InstanceIdentifier()
    {
    }
    
    std::string toString() const
    {
        std::stringstream ss;
        
        if (m_instance_id == ara::com::internal::INSTANCE_ID_UNKNOWN)
        {
            ss << "Any";
        }
        else
        {
            ss << m_instance_id;
        }
        
        return ss.str();
    }
    
    ara::com::internal::InstanceId GetInstanceId() const
    {
        return m_instance_id;
    }
    
    bool operator==(const InstanceIdentifier& other) const
    {
        return m_instance_id == other.m_instance_id;
    }
    
    bool operator<(const InstanceIdentifier& other) const
    {
        return GetInstanceId() < other.GetInstanceId();
    }
    
    InstanceIdentifier& operator=(const InstanceIdentifier& other)
    {
        m_instance_id = other.m_instance_id;
        
        return *this;
    }
    
    explicit operator ara::com::internal::InstanceId() const
    {
        return m_instance_id;
    }
    
    static const InstanceIdentifier Any;
    
private:
    
    ara::com::internal::InstanceId m_instance_id;    
};

// Method call processing modes for the service implementation side (skeleton).
enum class MethodCallProcessingMode
{
    kPoll,
    kEvent,
    kEventSingleThread
};

// Identifier for a triggered FindService request.
// This identifier is needed to later cancel the FindService request.
struct FindServiceHandle
{
    internal::ServiceId service_id;
    internal::InstanceId instance_id;
    std::uint32_t uid;
    
    bool operator==(const FindServiceHandle& other) const
    {
        return service_id == other.service_id && instance_id == other.instance_id && uid == other.uid;
    }
    
    bool operator<(const FindServiceHandle& other) const
    {
        return uid < other.uid;
    }
    
    FindServiceHandle& operator=(const FindServiceHandle& other)
    {
        service_id = other.service_id;
        instance_id = other.instance_id;
        uid = other.uid;
        
        return *this;
    }
};

// Fixed definition of update policy for Events.
enum class EventCacheUpdatePolicy
{
    kLastN,
    kNewestN
};

// Container for a list of service handles.
template <typename Handle>
using ServiceHandleContainer = std::vector<Handle>;

// Definition of the subscription state of an Event.
enum class SubscriptionState
{
    kSubscribed,
    kNotSubscribed,
    kSubscriptionPending
};

// Function representing a filter function provided by the programmer.
template <typename S>
using FilterFunction = std::function<bool(const S& sample)>;

// Receive handler method, which is semantically a void(void) function.
using EventReceiveHandler = std::function<void()>;

// Definition of the subscription state of an Event.
using SubscriptionStateChangeHandler = std::function<void(ara::com::SubscriptionState)>;

// Pointer to allocated sample on service side.
template <typename T>
using SampleAllocateePtr = std::unique_ptr<T>;

template <typename T>
using FieldGetHandler = std::function<ara::core::Future<T>()>;

template <typename T>
using FieldSetHandler = std::function<ara::core::Future<T>(const T& data)>;

// Handler that gets called in case service availability for services which have been searched for via FindService() has changed.
template <typename T>
using FindServiceHandler = std::function<void(ServiceHandleContainer<T>)>;

// Handler that gets called in case service availability for services which have been searched for via FindService() has changed.
template <typename T>
using FindServiceHandlerExt = std::function<void(ServiceHandleContainer<T>, FindServiceHandle)>;

// Container for a list of sample-pointers received via event communication.
template <typename SampleType>
using SampleContainer = std::vector<SampleType>;

}  // namespace com
}  // namespace ara

#endif  // ARA_COM_DATA_TYPES_H_
