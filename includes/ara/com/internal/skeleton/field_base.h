/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_SKELETON_FIELD_BASE_H_
#define ARA_COM_INTERNAL_SKELETON_FIELD_BASE_H_

#include <ara/com/types.h>
#include "skeleton_base.h"

namespace ara
{
namespace com
{
namespace internal
{
namespace skeleton
{

class FieldBase : protected SkeletonBase
{
public:
    FieldBase(ServiceSkeleton *service, std::string name);
    
    virtual ~FieldBase();
    
protected:
    std::string m_name;
};

} // skeleton
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_SKELETON_FIELD_BASE_H_
