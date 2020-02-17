/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_CORE_VECTOR_H_
#define ARA_CORE_VECTOR_H_

#include <vector>
#include <memory>
#include <type_traits>

namespace ara
{
namespace core
{

template <typename T, typename Allocator = std::allocator<T>>
using Vector = std::vector<T, Allocator>;

template <typename T,
    typename Allocator,
    typename = typename std::enable_if<!std::is_same<Vector<T, Allocator>, std::vector<T, Allocator>>::value>::type>
inline bool operator==(Vector<T, Allocator> const& lhs, Vector<T, Allocator> const& rhs)
{
    return std::operator==(lhs, rhs);
}

template <typename T,
    typename Allocator,
    typename = typename std::enable_if<!std::is_same<Vector<T, Allocator>, std::vector<T, Allocator>>::value>::type>
inline bool operator!=(Vector<T, Allocator> const& lhs, Vector<T, Allocator> const& rhs)
{
    return std::operator!=(lhs, rhs);
}

template <typename T,
    typename Allocator,
    typename = typename std::enable_if<!std::is_same<Vector<T, Allocator>, std::vector<T, Allocator>>::value>::type>
inline bool operator<(Vector<T, Allocator> const& lhs, Vector<T, Allocator> const& rhs)
{
    return std::operator<(lhs, rhs);
}

template <typename T,
    typename Allocator,
    typename = typename std::enable_if<!std::is_same<Vector<T, Allocator>, std::vector<T, Allocator>>::value>::type>
inline bool operator<=(Vector<T, Allocator> const& lhs, Vector<T, Allocator> const& rhs)
{
    return std::operator<=(lhs, rhs);
}

template <typename T,
    typename Allocator,
    typename = typename std::enable_if<!std::is_same<Vector<T, Allocator>, std::vector<T, Allocator>>::value>::type>
inline bool operator>(Vector<T, Allocator> const& lhs, Vector<T, Allocator> const& rhs)
{
    return std::operator>(lhs, rhs);
}

template <typename T,
    typename Allocator,
    typename = typename std::enable_if<!std::is_same<Vector<T, Allocator>, std::vector<T, Allocator>>::value>::type>
inline bool operator>=(Vector<T, Allocator> const& lhs, Vector<T, Allocator> const& rhs)
{
    return std::operator>=(lhs, rhs);
}

template <typename T,
    typename Allocator,
    typename = typename std::enable_if<!std::is_same<Vector<T, Allocator>, std::vector<T, Allocator>>::value>::type>
void swap(Vector<T, Allocator>& lhs, Vector<T, Allocator>& rhs)
{
    lhs.swap(rhs);
}

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_VECTOR_H_
