/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_CORE_MAP_H_
#define ARA_CORE_MAP_H_

#include <map>
#include <memory>
#include <type_traits>

namespace ara
{
namespace core
{

template <typename Key, typename T, typename Compare = std::less<Key>, typename Allocator = std::allocator<T>>
using Map = std::map<Key, T, Compare, Allocator>;

template <typename Key,
    typename T,
    typename Compare,
    typename Allocator,
    typename = typename std::enable_if<!std::is_same<Map<Key, T, Compare, Allocator>,
        std::map<Key, T, Compare, Allocator>>::value>::type>
void swap(Map<Key, T, Compare, Allocator>& lhs, Map<Key, T, Compare, Allocator>& rhs)
{
    lhs.swap(rhs);
}

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_MAP_H_
