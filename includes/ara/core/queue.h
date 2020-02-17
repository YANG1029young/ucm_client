/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_CORE_QUEUE_H_
#define ARA_CORE_QUEUE_H_

#include <queue>
#include <memory>
#include <type_traits>

namespace ara
{
namespace core
{

template <typename T, typename Container = std::deque<T>>
using Queue = std::queue<T, Container>;

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_QUEUE_H_
