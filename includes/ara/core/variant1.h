/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_CORE_VARIANT_H_
#define ARA_CORE_VARIANT_H_

// GCC >= 7.3
#if __GNUC__ == 7 && __GNUC_MINOR__ >= 3

#include <variant>

namespace ara
{
namespace core
{

//Variant Class Template
template< class... Types >
class Variant : public std::variant<Types...>
{
using _Base = std::variant<Types...>;
public:
    // Default constructor
    Variant() noexcept = default;
    
    // Move constructor
    Variant(Variant&&) noexcept = default;
    
    // Copy constructor
    Variant(const Variant&) = default;
    
    template<class Tp>
    Variant(Tp&& t)
        :_Base(t)
    {
    }
    
    ~Variant() = default;
    
    // Move assignment operator
    Variant& operator=(Variant&&) noexcept = default;
    
    // Default copy assignment operator
    Variant& operator=(const Variant&) = default;
    
    template<class Tp>
    Variant& operator=(Tp&& rhs)
    {
        _Base::operator=(rhs);
        return *this;
    }
    
    // Returns the zero-based index of the alternative
    constexpr std::size_t index() const
    {
        return _Base::index();
    }
    
    // Checks if the Variant is an invalid state
    bool valueless_by_exception() const noexcept
    {
        return _Base::valueless_by_exception();
    }
};

}  // namespace core
}  // namespace ara

#else

#include <type_traits>
#include <utility>
#include <bits/enable_special_members.h>
#include <bits/functexcept.h>
#include <bits/move.h>
#include <bits/functional_hash.h>
#include <bits/invoke.h>
#include <ext/aligned_buffer.h>
#include <bits/parse_numbers.h>
#include <bits/stl_iterator_base_types.h>
#include <bits/stl_iterator_base_funcs.h>
#include <bits/stl_construct.h>

#endif // __GNUC__ == 7 && __GNUC_MINOR__ >= 3

#endif  // ARA_CORE_VARIANT_H_
