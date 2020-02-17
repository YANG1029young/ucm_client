/*!
* @file
* @brief Adds support for make_unique if it was not defined for given c++ version
*/

#ifndef ARA_PER_FILEACCESS_SMART_PTR_H_
#define ARA_PER_FILEACCESS_SMART_PTR_H_

#include <memory>
#include <utility>

namespace ara
{
namespace per
{
#if __cplusplus <= 201103L  // support of lower version from C++11

template <typename _Tp, typename... Args>
std::unique_ptr<_Tp> make_unique(Args&&... args)
{
    return std::unique_ptr<_Tp>(new _Tp(std::forward<Args>(args)...));
}

#else  // C++14 supports make_unique feature

using std::make_unique;

#endif
}  // namespace per
}  // namespace ara

#endif  // ARA_PER_FILEACCESS_SMART_PTR_H_
