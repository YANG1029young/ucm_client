/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_BINDING_COMMON_H_
#define ARA_COM_INTERNAL_BINDING_COMMON_H_

#include <ara/com/data_types.h>
#include <ara/com/internal/manifest.h>

namespace ara
{
namespace com
{
namespace internal
{
namespace binding
{

template <typename T, typename Tagged = void>
struct is_enumerable
{
    static const bool value = false;
};

template <typename T>
struct is_enumerable<T, typename T::IsEnumerableTag>
{
    static const bool value = true;
};

}  // namespace binding
}  // namespace internal
}  // namespace com
}  // namespace ara

#endif // ARA_COM_INTERNAL_BINDING_COMMON_H_ 
