/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_PROXY_EVENT_H_
#define ARA_COM_INTERNAL_PROXY_EVENT_H_

#include <ara/com/types.h>
#include "event_base.h"

namespace ara
{
namespace com
{
namespace internal
{
namespace proxy
{

template <typename T>
class Event : public EventBase
{
public:
    Event(ServiceProxy* service, std::string name)
        :EventBase(service, name)
    {
    }
    
    virtual ~Event(){}
    
    bool Update(ara::com::FilterFunction<T> filter = {})
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        
        if (m_cacheSize == 0)
        {
            return false;
        }
        
        if (m_policy == ara::com::EventCacheUpdatePolicy::kNewestN)
        {
            m_samples.clear();
        }
                
        UpdateEventSample(m_name, m_samples, m_data, filter, m_cacheSize);
        
        m_data.clear();

        return !m_samples.empty();
    }
    
    const ara::com::SampleContainer<ara::com::SamplePtr<const T>>& GetCachedSamples() const
    {
        return m_samples;
    }
    
    void Cleanup()
    {
        if (m_policy == ara::com::EventCacheUpdatePolicy::kNewestN)
        {
            std::lock_guard<std::mutex> guard(m_mutex);
            m_samples.clear();
        }
        
        EventBase::Cleanup();
    }
    
private:
    ara::com::SampleContainer<ara::com::SamplePtr<const T>> m_samples;
};

} // proxy
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_PROXY_EVENT_H_
