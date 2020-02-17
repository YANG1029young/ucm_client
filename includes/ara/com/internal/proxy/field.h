/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_PROXY_FIELD_H_
#define ARA_COM_INTERNAL_PROXY_FIELD_H_

#include <ara/com/types.h>
#include "field_base.h"
#include "event.h"

namespace ara
{
namespace com
{
namespace internal
{
namespace proxy
{

template <typename T>
class Field : public Event<T>
{
public:
    Field(ServiceProxy* service, std::string name)
        :Event<T>(service, name)
    {
    }
    
    virtual ~Field(){}
    
    ara::core::Future<T> Get()
    {
        return EventBase::SendRequest<T>(EventBase::m_name + "_Get");
    }
    
    ara::core::Future<T> Set(const T& value)
    {
        return EventBase::SendRequest<T>(EventBase::m_name + "_Set", value);
    }
};

template <typename T>
class FieldNoSetter : public Event<T>
{
public:
    FieldNoSetter(ServiceProxy* service, std::string name)
        :Event<T>(service, name)
    {
    }
    
    virtual ~FieldNoSetter(){}
    
    ara::core::Future<T> Get()
    {
        return EventBase::SendRequest<T>(EventBase::m_name + "_Get");
    }
};

template <typename T>
class FieldNoGetter : public Event<T>
{
public:
    FieldNoGetter(ServiceProxy* service, std::string name)
        :Event<T>(service, name)
    {
    }
    
    virtual ~FieldNoGetter(){}
    
    ara::core::Future<T> Set(const T& value)
    {
        return EventBase::SendRequest<T>(EventBase::m_name + "_Set", value);
    }
};

template <typename T>
class FieldNoGetterAndSetter : public Event<T>
{
public:
    FieldNoGetterAndSetter(ServiceProxy* service, std::string name)
        :Event<T>(service, name)
    {
    }
    
    virtual ~FieldNoGetterAndSetter(){}
};

template <typename T>
class FieldNoNotifier : public FieldBase
{
public:
    FieldNoNotifier(ServiceProxy* service, std::string name)
        :FieldBase(service, name)
    {
    }
    
    virtual ~FieldNoNotifier(){}
    
    ara::core::Future<T> Get()
    {
        return SendRequest<T>(m_name + "_Get");
    }
    
    ara::core::Future<T> Set(const T& value)
    {
        return SendRequest<T>(m_name + "_Set", value);
    }
};

template <typename T>
class FieldNoNotifierAndSetter : public FieldBase
{
public:
    FieldNoNotifierAndSetter(ServiceProxy* service, std::string name)
        :FieldBase(service, name)
    {
    }
    
    virtual ~FieldNoNotifierAndSetter(){}
    
    ara::core::Future<T> Get()
    {
        return SendRequest<T>(m_name + "_Get");
    }
};

template <typename T>
class FieldNoNotifierAndGetter : public FieldBase
{
public:
    FieldNoNotifierAndGetter(ServiceProxy* service, std::string name)
        :FieldBase(service, name)
    {
    }
    
    virtual ~FieldNoNotifierAndGetter(){}
    
    ara::core::Future<T> Set(const T& value)
    {
        return SendRequest<T>(m_name + "_Set", value);
    }
};

template <typename T, bool hasGetter, bool hasNotifier, bool hasSetter>
struct FieldType
{
    using type = typename FieldType<T, hasNotifier, hasGetter, hasSetter>::type;
};

template <typename T>
struct FieldType<T,true,true,true>
{
    using type = Field<T>;
};

template <typename T>
struct FieldType<T,true,true,false>
{
    using type = FieldNoSetter<T>;
};

template <typename T>
struct FieldType<T,false,true,true>
{
    using type = FieldNoGetter<T>;
};

template <typename T>
struct FieldType<T,false,true,false>
{
    using type = FieldNoGetterAndSetter<T>;
};

template <typename T>
struct FieldType<T,true,false,true>
{
    using type = FieldNoNotifier<T>;
};

template <typename T>
struct FieldType<T,true,false,false>
{
    using type = FieldNoNotifierAndSetter<T>;
};

template <typename T>
struct FieldType<T,false,false,true>
{
    using type = FieldNoNotifierAndGetter<T>;
};

} // proxy
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_PROXY_FIELD_H_
