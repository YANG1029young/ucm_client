/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_SKELETON_EVENT_H_
#define ARA_COM_INTERNAL_SKELETON_EVENT_H_

#include <ara/com/types.h>
#include "event_base.h"

namespace ara
{
namespace com
{
namespace internal
{
namespace skeleton
{

template <typename T>
class Event : public EventBase
{
public:
    Event(ServiceSkeleton *service, std::string name)
        :EventBase(service, name)
    {
    }
    
    virtual ~Event(){}
    
    void Send(const T& data)
    {
        SendEvent(m_name, data, false);
    }
    
    void Send(ara::com::SampleAllocateePtr<T> data)
    {
        Send(*data);
    }
    
    ara::com::SampleAllocateePtr<T> Allocate()
    {
        return std::make_unique<T>();
    }
};

} // skeleton
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_SKELETON_EVENT_H_
