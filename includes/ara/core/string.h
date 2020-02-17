/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_CORE_STRING_H_
#define ARA_CORE_STRING_H_

#include <string>
#include <type_traits>

namespace ara
{
namespace core
{

using String = std::basic_string<char>;

template <typename Dummy = void,
    typename = typename std::enable_if<!std::is_same<String, std::string>::value, Dummy>::type>
void swap(String& lhs, String& rhs)
{
    lhs.swap(rhs);
}

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_STRING_H_
