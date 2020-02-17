/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_PROXY_METHOD_BASE_H_
#define ARA_COM_INTERNAL_PROXY_METHOD_BASE_H_

#include <ara/com/types.h>
#include "proxy_base.h"

namespace ara
{
namespace com
{
namespace internal
{
namespace proxy
{

class MethodBase : public ProxyBase
{
public:
    MethodBase(ServiceProxy* service, std::string name);
    virtual ~MethodBase();

protected:
    std::string m_name;
};

} // proxy
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_PROXY_METHOD_BASE_H_
