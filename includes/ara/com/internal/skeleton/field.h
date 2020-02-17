/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_SKELETON_FIELD_H_
#define ARA_COM_INTERNAL_SKELETON_FIELD_H_

#include <ara/com/types.h>
#include "field_base.h"

namespace ara
{
namespace com
{
namespace internal
{
namespace skeleton
{

template <typename T>
class Field : public FieldBase
{
public:
    Field(ServiceSkeleton* service, std::string name)
        :FieldBase(service, name), GetHandler(nullptr), SetHandler(nullptr)
    {
    }
    
    virtual ~Field(){}
    
    void Update(const T& data)
    {
        SendEvent(m_name, data, true);
    }
    
    void RegisterGetHandler(ara::com::FieldGetHandler<T> getHandler)
    {
        GetHandler = getHandler;
    }
    
    void RegisterSetHandler(ara::com::FieldSetHandler<T> setHandler)
    {
        SetHandler = setHandler;
    }
    
    ara::com::FieldGetHandler<T> GetHandler;
    ara::com::FieldSetHandler<T> SetHandler;
};

template <typename T>
class FieldNoSetter : public FieldBase
{
public:
    FieldNoSetter(ServiceSkeleton* service, std::string name)
        :FieldBase(service, name), GetHandler(nullptr)
    {
    }
    
    virtual ~FieldNoSetter(){}
    
    void Update(const T& data)
    {
        SendEvent(m_name, data, true);
    }
    
    void RegisterGetHandler(ara::com::FieldGetHandler<T> getHandler)
    {
        GetHandler = getHandler;
    }
    
    ara::com::FieldGetHandler<T> GetHandler;
};

template <typename T>
class FieldNoGetter : public FieldBase
{
public:
    FieldNoGetter(ServiceSkeleton* service, std::string name)
        :FieldBase(service, name), SetHandler(nullptr)
    {
    }
    
    virtual ~FieldNoGetter(){}
    
    void Update(const T& data)
    {
        SendEvent(m_name, data, true);
    }
    
    void RegisterSetHandler(ara::com::FieldSetHandler<T> setHandler)
    {
        SetHandler = setHandler;
    }
    
    ara::com::FieldSetHandler<T> SetHandler;
};

template <typename T>
class FieldNoGetterAndSetter : public FieldBase
{
public:
    FieldNoGetterAndSetter(ServiceSkeleton* service, std::string name)
        :FieldBase(service, name)
    {
    }
    
    virtual ~FieldNoGetterAndSetter(){}
    
    void Update(const T& data)
    {
        SendEvent(m_name, data, true);
    }
};

template <typename T>
class FieldNoNotifier : public FieldBase
{
public:
    FieldNoNotifier(ServiceSkeleton* service, std::string name)
        :FieldBase(service, name), GetHandler(nullptr), SetHandler(nullptr)
    {
    }
    
    virtual ~FieldNoNotifier(){}
    
    void RegisterGetHandler(ara::com::FieldGetHandler<T> getHandler)
    {
        GetHandler = getHandler;
    }
    
    void RegisterSetHandler(ara::com::FieldSetHandler<T> setHandler)
    {
        SetHandler = setHandler;
    }
    
    ara::com::FieldGetHandler<T> GetHandler;
    ara::com::FieldSetHandler<T> SetHandler;
};

template <typename T>
class FieldNoNotifierAndSetter : public FieldBase
{
public:
    FieldNoNotifierAndSetter(ServiceSkeleton* service, std::string name)
        :FieldBase(service, name), GetHandler(nullptr)
    {
    }
    
    virtual ~FieldNoNotifierAndSetter(){}
    
    void RegisterGetHandler(ara::com::FieldGetHandler<T> getHandler)
    {
        GetHandler = getHandler;
    }
    
    ara::com::FieldGetHandler<T> GetHandler;
};

template <typename T>
class FieldNoNotifierAndGetter : public FieldBase
{
public:
    FieldNoNotifierAndGetter(ServiceSkeleton* service, std::string name)
        :FieldBase(service, name), SetHandler(nullptr)
    {
    }
    
    virtual ~FieldNoNotifierAndGetter(){}
    
    void RegisterSetHandler(ara::com::FieldSetHandler<T> setHandler)
    {
        SetHandler = setHandler;
    }
    
    ara::com::FieldSetHandler<T> SetHandler;
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

} // skeleton
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_SKELETON_FIELD_H_
