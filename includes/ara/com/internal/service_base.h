/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_SERVICE_BASE_H_
#define ARA_COM_INTERNAL_SERVICE_BASE_H_

#include <ara/com/internal/manifest.h>

namespace ara
{
namespace com
{
namespace internal
{

class ServiceBase
{
public:
    ServiceBase(std::string name);
    
    virtual ~ServiceBase();
    
protected:
    void addMethod(std::string name);
    void addEvent(std::string name);
    void addField(std::string name, bool hasGetter = true, bool hasNotifier = true, bool hasSetter = true);
    
    std::string m_name;;
    std::shared_ptr<ara::com::internal::ServiceInterface> m_serviceInterface;
};

} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_SERVICE_BASE_H_
