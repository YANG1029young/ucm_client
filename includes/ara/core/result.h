

#ifndef ARA_CORE_RESULT_H_
#define ARA_CORE_RESULT_H_

#include "ara/core/error_code.h"

#include <variant>
#include <system_error>
#include <type_traits>
#include <memory>
#include <utility>
#include <iostream>

namespace ara
{
namespace core
{

template <typename T, typename E = ErrorCode>
class Result
{
    std::variant<T, E> mData;

public:
    static Result FromValue(T const& t)
    {
        return Result(t);
    }

    static Result FromValue(T&& t)
    {
        return Result(std::move(t));
    }

    template <typename... Args>
    static Result FromValue(Args&&... args)
    {
        return Result(T(std::forward<Args>(args)...));
    }

    // ----------------------------------------

    static Result FromError(E const& e)
    {
        return Result(e);
    }

    static Result FromError(E&& e)
    {
        return Result(std::move(e));
    }

    template <typename... Args>
    static Result FromError(Args&&... args)
    {
        return Result(E(std::forward<Args>(args)...));
    }

    // ----------------------------------------

    constexpr Result(T const& t)
        : mData(t)
    {
    }

    constexpr Result(T&& t)
        : mData(std::move(t))
    {
    }

    constexpr explicit Result(E const& e)
        : mData(e)
    {
    }

    constexpr explicit Result(E&& e)
        : mData(std::move(e))
    {
    }

    // ----------------------------------------

    template <typename... Args>
    void EmplaceValue(Args&&... args)
    {
        // Unfortunately, variant does not support emplace() for template, so we fall back to assignment here.
        mData = std::move(T(std::forward<Args>(args)...));
    }

    template <typename... Args>
    void EmplaceError(Args&&... args)
    {
        // Unfortunately, variant does not support emplace() for template, so we fall back to assignment here.
        mData = std::move(E(std::forward<Args>(args)...));
    }

    void swap(Result& other) noexcept(
        std::is_nothrow_move_constructible<T>::value&& std::is_nothrow_move_assignable<T>::value)
    {
        using std::swap;
        swap(mData, other.mData);
    }

    constexpr explicit operator bool() const noexcept
    {
        return HasValue();
    }

    constexpr bool HasValue() const noexcept
    {
        return mData.index() == 0;
    }

    constexpr T const& operator*() const
    {
        return Value();
    }

    constexpr T const* operator->() const
    {
        return std::addressof(Value());
    }

    constexpr T const& Value() const &
    {
        T const* ptr = std::get_if<T>(&mData);
        if (ptr)
            return *ptr;
        std::cout << "__ value() called but NOT a value!\n";
        std::terminate();
    }

    T& Value() &
    {
        T* ptr = std::get_if<T>(&mData);
        if (ptr)
            return *ptr;
        std::cout << "__ value() called but NOT a value!\n";
        std::terminate();
    }

    T&& Value() &&
    {
        T* ptr = std::get_if<T>(&mData);
        if (ptr)
            return std::move(*ptr);
        std::cout << "__ value() called but NOT a value!\n";
        std::terminate();
    }

    constexpr E const& Error() const
    {
        E const* ptr = std::get_if<E>(&mData);
        if (ptr)
            return *ptr;
        std::cout << "__ error() called but NOT an error!\n";
        std::terminate();
    }

    template <typename U>
    constexpr T ValueOr(U&& defaultValue) const
    {
        return HasValue() ? Value() : static_cast<T>(std::forward<U>(defaultValue));
    }

    template <typename G>
    constexpr E ErrorOr(G&& defaultError) const
    {
        return HasValue() ? static_cast<E>(std::forward<G>(defaultError)) : Error();
    }

    template <typename G>
    constexpr bool CheckError(G&& e) const
    {
        return HasValue() ? false : (Error() == static_cast<E>(std::forward<G>(e)));
    }

#ifndef ARA_NO_EXCEPTIONS
    T const& ValueOrThrow() noexcept(false)
    {
        T const* ptr = std::get_if<T>(&mData);
        if (ptr)
            return *ptr;

        // TODO: check if mData is uninitialized (-> monostate)
        E* e = std::get_if<E>(&mData);

        e->ThrowAsException();
    }
#endif

    template <typename F>
    constexpr T Resolve(F&& f) const
    {
        return HasValue() ? Value() : std::forward<F>(f)(Error());
    }

    // Re-implementation of C++14's std::enable_if_t
    template <bool Condition, typename U = void>
    using enable_if_t = typename std::enable_if<Condition, U>::type;

    // Re-implementation of C++14's std::result_of_t
    template <typename U>
    using result_of_t = typename std::result_of<U>::type;

    /// @brief Trait that detects whether a type is a Result<...>
    template <typename U>
    struct is_result : std::false_type
    {
    };

    template <typename U, typename G>
    struct is_result<Result<U, G>> : std::true_type
    {
    };

    template <typename F>
    using CallableReturnsResult = enable_if_t<is_result<result_of_t<F(T const&)>>::value>;

    template <typename F>
    using CallableReturnsNoResult = enable_if_t<!is_result<result_of_t<F(T const&)>>::value>;

    template <typename F, typename = CallableReturnsResult<F>>
    auto Bind(F&& f) const -> decltype(f(Value()))
    {
        using U = decltype(f(Value()));
        return HasValue() ? std::forward<F>(f)(Value()) : U(Error());
    }

    template <typename F, typename = CallableReturnsNoResult<F>>
    auto Bind(F&& f) const -> Result<decltype(f(Value())), E>
    {
        using U = decltype(f(Value()));
        using R = Result<U, E>;
        return HasValue() ? std::forward<F>(f)(Value()) : R(Error());
    }

    template <typename, typename>
    friend class Result;
};

template <typename T, typename E>
inline void swap(Result<T, E>& lhs, Result<T, E>& rhs) noexcept(noexcept(lhs.swap(rhs)))
{
    lhs.swap(rhs);
}

//
// Specialization for void
//

template <typename E>
class Result<void, E>
{
    // Cannot use 'void' for variant, so define our own (default-constructible) dummy type instead.
    struct dummy
    {
    };
    using T = dummy;
    std::variant<T, E> mData;

public:
    static Result FromValue()
    {
        return Result();
    }

    static Result FromError(E const& e)
    {
        return Result(e);
    }

    static Result FromError(E&& e)
    {
        return Result(std::move(e));
    }

    template <typename... Args>
    static Result FromError(Args&&... args)
    {
        return Result(E{std::forward<Args>(args)...});
    }

    // ----------------------------------------

    constexpr Result() noexcept
        : mData(T{})
    {
    }

    constexpr explicit Result(E const& e)
        : mData(e)
    {
    }

    constexpr explicit Result(E&& e)
        : mData(std::move(e))
    {
    }

    // ----------------------------------------

    template <typename... Args>
    void EmplaceValue(Args&&... args) noexcept
    {
        mData = T(args...);
    }

    template <typename... Args>
    void EmplaceError(Args&&... args)
    {
        // Unfortunately, Boost.Variant does not support emplace(), so we fall back to assignment here.
        mData = std::move(E(std::forward<Args>(args)...));
    }

    void swap(Result& other) noexcept
    {
        using std::swap;
        swap(mData, other.mData);
    }

    constexpr explicit operator bool() const noexcept
    {
        return HasValue();
    }

    constexpr bool HasValue() const noexcept
    {
        return mData.index() == 0;
    }

    constexpr void Value() const
    {
        T const* ptr = std::get_if<T>(&mData);
        if (ptr)
            return;
        std::cout << "__ value() called but NOT a (void) value!\n";
        std::terminate();
    }

    constexpr E const& Error() const
    {
        E const* ptr = std::get_if<E>(&mData);
        if (ptr)
            return *ptr;
        std::cout << "__ error() called but NOT an error!\n";
        std::terminate();
    }

    template <typename G>
    constexpr E ErrorOr(G&& defaultError) const
    {
        return HasValue() ? static_cast<E>(std::forward<G>(defaultError)) : Error();
    }

    template <typename G>
    constexpr bool CheckError(G&& e) const
    {
        return HasValue() ? false : (Error() == static_cast<E>(std::forward<G>(e)));
    }

#ifndef ARA_NO_EXCEPTIONS
    void ValueOrThrow() noexcept(false)
    {
        T const* ptr = std::get_if<T>(&mData);
        if (ptr)
            return;
        
        E* e = std::get_if<E>(&mData);
        e->ThrowAsException();
    }
#endif

    template <typename F>
    constexpr void Resolve(F&& f) const
    {
        return HasValue() ? Value() : std::forward<F>(f)(Error());
    }
};

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_RESULT_H_
