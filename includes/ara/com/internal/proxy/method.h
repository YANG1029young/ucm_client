/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_PROXY_METHOD_H_
#define ARA_COM_INTERNAL_PROXY_METHOD_H_

#include <ara/com/types.h>
#include "method_base.h"

namespace ara
{
namespace com
{
namespace internal
{
namespace proxy
{

template <typename T>
class Method;

template <typename T>
class FireAndForgetMethod;

template <typename... Args>
class Method<void(Args...)> : private MethodBase
{
public:
    Method(ServiceProxy* service, std::string name)
        :MethodBase(service, name)
    {
    }
    
    virtual ~Method(){}
    
    ara::core::Future<void> operator()(Args&&... args)
    {
        return SendRequest(m_name, std::forward<Args>(args)...);
    }
};

template <typename R, typename... Args>
class Method<R(Args...)> : private MethodBase
{
public:
    Method(ServiceProxy* service, std::string name)
        :MethodBase(service, name)
    {
    }
    
    virtual ~Method(){}
    
    ara::core::Future<R> operator()(Args&&... args)
    {
        return SendRequest<R>(m_name, std::forward<Args>(args)...);
    }
};

template <typename... Args>
class FireAndForgetMethod<void(Args...)> : private MethodBase
{
public:
    FireAndForgetMethod(ServiceProxy* service, std::string name)
        :MethodBase(service, name)
    {
    }
    
    virtual ~FireAndForgetMethod(){}
    
    void operator()(Args&&... args)
    {
        return SendFireAndForgetRequest(m_name, std::forward<Args>(args)...);
    }
};

} // proxy
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_PROXY_METHOD_H_
