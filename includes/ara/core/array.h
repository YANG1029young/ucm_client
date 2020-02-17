/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_CORE_ARRAY_H_
#define ARA_CORE_ARRAY_H_

#include <array>
#include <type_traits>

namespace ara
{
namespace core
{

template <typename T, std::size_t N>
using Array = std::array<T, N>;

template <typename T,
    std::size_t N,
    typename = typename std::enable_if<!std::is_same<Array<T, N>, std::array<T, N>>::value>::type>
void swap(Array<T, N>& lhs, Array<T, N>& rhs)
{
    lhs.swap(rhs);
}

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_ARRAY_H_
