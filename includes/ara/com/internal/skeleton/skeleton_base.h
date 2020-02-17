/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_SKELETON_SKELETON_BASE_H_
#define ARA_COM_INTERNAL_SKELETON_SKELETON_BASE_H_

#include <ara/com/types.h>
#include "service_skeleton.h"

namespace ara
{
namespace com
{
namespace internal
{
namespace skeleton
{

class SkeletonBase
{
protected:
    SkeletonBase(ServiceSkeleton *service);
    
    virtual ~SkeletonBase();
    
    template <typename T>
    void SendEvent(std::string eventName, const T& data, bool is_field)
    {
        m_service->SendEvent(eventName, data, is_field);
    }

private:    
    ServiceSkeleton* m_service;
};

} // skeleton
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_SKELETON_SKELETON_BASE_H_
