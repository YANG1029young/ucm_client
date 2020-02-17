/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */
 
#ifndef ARA_CORE_FUTURE_H_
#define ARA_CORE_FUTURE_H_

#include <chrono>
#include <future>
#include <assert.h>

#include "internal/state.h"
#include "error_code.h"
#include "ara/core/result.h"
#include "ara/core/posix_error.h"

namespace ara
{
namespace core
{
template <typename, typename>
class Promise;

/**
 * @brief Specifies the state of a Future as returned by wait_for() and wait_until().
 *
 * These definitions are equivalent to the ones from std::future_status. However, the
 * item std::future_status::deferred is not supported here.
 */
enum class FutureStatus : uint8_t
{
    ready = 1,  // the shared state is ready
    timeout,  // the shared state did not become ready before the specified timeout has passed
};

enum class future_errc : int32_t
{
    broken_promise = 128,
    future_already_retrieved,
    promise_already_satisfied,
    no_state,
};

class FutureException : public Exception
{
public:
    /**
     * @brief Construct a new future exception object containing an Error object.
     */
    explicit FutureException(ErrorCode&& err) noexcept
        : Exception(std::move(err))
    {
    }
};

class FutureErrorDomain : public ErrorDomain
{
    constexpr static ErrorDomain::IdType kId = 0x029f881224e61118LL;

public:
    using Errc = future_errc;
    using Exception = FutureException;

    constexpr FutureErrorDomain() noexcept
        : ErrorDomain(kId)
    {
    }

    char const* Name() const noexcept override
    {
        return "Future";
    }

    char const* Message(ErrorDomain::CodeType errorCode) const noexcept override
    {
        Errc const code = static_cast<Errc>(errorCode);
        switch (code) {
        case Errc::broken_promise:
            return "broken promise";
        case Errc::future_already_retrieved:
            return "future already retrieved";
        case Errc::promise_already_satisfied:
            return "promise already satisfied";
        case Errc::no_state:
            return "no state associated with this future";
        default:
            return "unknown future error";
        }
    }

    void ThrowAsException(ErrorCode const& errorCode) const noexcept(false) override
    {
        ThrowOrTerminate<Exception>(errorCode);
    }
};

namespace internal
{
constexpr FutureErrorDomain g_futureErrorDomain;
}

inline constexpr ErrorDomain const& GetFutureDomain()
{
    return internal::g_futureErrorDomain;
}

inline constexpr ErrorCode MakeErrorCode(FutureErrorDomain::Errc code,
    ErrorDomain::SupportDataType data,
    char const* message)
{
    return ErrorCode(static_cast<ErrorDomain::CodeType>(code), GetFutureDomain(), data, message);
}

/**
 * \brief Provides ara::core specific Future operations to collect the results of an asynchronous call.
 *
 * Much of its functionality is delegated to std::future and all methods that resemble std::future are guaranteed to
 * behave the same.
 */
template <typename T, typename E = ErrorCode>
class Future
{
    using R = Result<T, E>;

public:
    // Default constructor
    Future() noexcept = default;
    
    // Move constructor
    Future(Future&& other) noexcept
        : delegate_future_(std::move(other.delegate_future_))
        , extra_state_(std::move(other.extra_state_))
        , mutex_()
    {
    }
    
    // Default copy constructor deleted
    Future(Future const&) = delete;
    
    // Specialized unwrapping constructor
    Future(Future<Future<T>>&& other) noexcept
        : mutex_()
    {
        if (other.valid())
        {
            if (other.is_ready())
            {
                try
                {
                    Future<T> f = other.get();
                    delegate_future_ = (std::move(f.delegate_future_));
                    extra_state_ = (std::move(f.extra_state_));
                }
                catch(...)
                {
                }
            }
        }
    }

    ~Future()
    {
        if (extra_state_ && extra_state_.use_count() == 1)
        {
            extra_state_->SetCallback(nullptr);
        }
    }
    
    // Move assignment operator
    Future& operator=(Future<T>&& other)
    {
        delegate_future_ = std::move(other.delegate_future_);
        extra_state_ = std::move(other.extra_state_);
        
        return *this;
    }
    
    // Default copy assignment operator deleted
    Future& operator=(Future const&) = delete;

     R GetResult()
    {
#ifndef ARA_NO_EXCEPTIONS
        try {
            return delegate_future_.get();
        } catch (std::future_error const& ex) {
            std::error_code const& ec = ex.code();
            future_errc err;
            if (ec == std::future_errc::broken_promise) {
                err = future_errc::broken_promise;
            } else if (ec == std::future_errc::future_already_retrieved) {
                err = future_errc::future_already_retrieved;
            } else if (ec == std::future_errc::promise_already_satisfied) {
                err = future_errc::promise_already_satisfied;
            } else if (ec == std::future_errc::no_state) {
                err = future_errc::no_state;
            } else {
                // Should rather use a vendor/demonstrator-specific ErrorDomain here?
                return R::FromError(posix_errc::invalid_argument);
            }
            R r = R::FromError(err);
            return r;
        }
#else
        // TODO: Somehow query the future object whether it contains an exception,
        // and if so, translate it into a Result<...>
        // This does not seem possible with C++14's std::future, because it lacks boost::future's
        // has_exception() method. Unfortunately, boost::future cannot be compiled with
        // -fno-exceptions, so that one is out as well.
        return delegate_future_.get();
#endif
    }
    
    // Returns the result
    T get()
    {
        //return delegate_future_.get();
        return GetResult().ValueOrThrow();
    }

    // Check if the Future has any shared state
    bool valid() const
    {
        return delegate_future_.valid();
    }

    // Block until the shared state is ready.
    void wait() const
    {
        delegate_future_.wait();
    }

    // Wait for a specified relative time.
    template <class Rep, class Period>
    FutureStatus wait_for(const std::chrono::duration<Rep, Period>& timeout_duration) const
    {
        switch (delegate_future_.wait_for(timeout_duration))
        {
        case std::future_status::ready:
            return FutureStatus::ready;
        case std::future_status::timeout:
            return FutureStatus::timeout;
        default:
            assert(!"this std::future_status should not occur in our setup");
        }
    }

    // Wait until a specified absolute time.
    template <typename Clock, typename Duration>
    FutureStatus wait_until(const std::chrono::time_point<Clock, Duration>& deadline) const
    {
        switch (delegate_future_.wait_until(deadline))
        {
        case std::future_status::ready:
            return FutureStatus::ready;
        case std::future_status::timeout:
            return FutureStatus::timeout;
        default:
            assert(!"this std::future_status should not occur in our setup");
        }
    }

    // Set a continuation for when the shared state is ready
    template <typename F>
    auto then(F&& func) -> Future<decltype(func(std::move(*this)))>
    {
        std::unique_lock<std::mutex> lock(mutex_);
        
        using type = decltype(func(std::move(*this)));
        std::shared_ptr<Promise<type,E>> p = std::make_shared<Promise<type,E>>();
        Future<type> f = p->get_future();
        
        extra_state_->SetCallback([func,p,this](){
                p->set_value(func(std::move(*this)));
            });
//        if (is_ready()) {
//            extra_state_->FireCallback();
//        }
       
        return f;
    }

    // Return true only when the shared state is ready
    bool is_ready() const
    {
        return std::future_status::ready == delegate_future_.wait_for(std::chrono::seconds::zero());
    }

private:
    /**
     *
     * \private
     *
     * \brief Constructs a future from a given std::future and a pointer to the extra state that is shared with the
     * promise
     * \param delegate_future std::future that complies to C++11 and is used whenever functionality from C++11 is
     * needed.
     * \param extra_state State that is shared with its ara::core::Promise.
     */
    Future(std::future<R>&& delegate_future, internal::State::Ptr extra_state)
        : delegate_future_(std::move(delegate_future))
        , extra_state_(extra_state)
        , mutex_()
    {
    }

    std::future<R> delegate_future_;
    internal::State::Ptr extra_state_;
    std::mutex mutex_;
    template <typename, typename>
    friend class Promise;
};

/**
 * \brief Provides ara::core specific Future operations to collect the results of an asynchronous call.
 *
 * Much of its functionality is delegated to std::future and all methods that resemble std::future are guaranteed to
 * behave the same.
 */
template <typename E>
class Future<void,E>
{
    using R = Result<void, E>;

public:
    // Default constructor
    Future() noexcept = default;
    
    // Move constructor
    Future(Future&& other) noexcept
        : delegate_future_(std::move(other.delegate_future_))
        , extra_state_(std::move(other.extra_state_))
        , mutex_()
    {
    }
    
    // Default copy constructor deleted
    Future(Future const&) = delete;
    
    // Specialized unwrapping constructor
    Future(Future<Future<void>>&& other) noexcept
        : mutex_()
    {
        if (other.valid())
        {
            if (other.is_ready())
            {
                try
                {
                    Future<void> f = other.get();
                    delegate_future_ = (std::move(f.delegate_future_));
                    extra_state_ = (std::move(f.extra_state_));
                }
                catch(...)
                {
                }
            }
        }
    }

    ~Future()
    {
        if (extra_state_ && extra_state_.use_count() == 1)
        {
            extra_state_->SetCallback(nullptr);
        }
    }
    
    // Move assignment operator
    Future& operator=(Future<void>&& other)
    {
        delegate_future_ = std::move(other.delegate_future_);
        extra_state_ = std::move(other.extra_state_);
        
        return *this;
    }
    
    // Default copy assignment operator deleted
    Future& operator=(Future const&) = delete;

     R GetResult()
    {
#ifndef ARA_NO_EXCEPTIONS
        try {
//            delegate_future_.get();
//            R r = R::FromValue();
//            return r;
            return delegate_future_.get();
        } catch (std::future_error const& ex) {
            std::error_code const& ec = ex.code();
            future_errc err;
            if (ec == std::future_errc::broken_promise) {
                err = future_errc::broken_promise;
            } else if (ec == std::future_errc::future_already_retrieved) {
                err = future_errc::future_already_retrieved;
            } else if (ec == std::future_errc::promise_already_satisfied) {
                err = future_errc::promise_already_satisfied;
            } else if (ec == std::future_errc::no_state) {
                err = future_errc::no_state;
            } else {
                // Should rather use a vendor/demonstrator-specific ErrorDomain here?
                return R::FromError(posix_errc::invalid_argument);
            }
            R r = R::FromError(err);
            return r;
        }
#else
        // TODO: Somehow query the future object whether it contains an exception,
        // and if so, translate it into a Result<...>
        // This does not seem possible with C++14's std::future, because it lacks boost::future's
        // has_exception() method. Unfortunately, boost::future cannot be compiled with
        // -fno-exceptions, so that one is out as well.
        return delegate_future_.get();
#endif
    }
    
    // Returns the result
    void get()
    {
        //return delegate_future_.get();
        return GetResult().ValueOrThrow();
    }

    // Check if the Future has any shared state
    bool valid() const
    {
        return delegate_future_.valid();
    }

    // Block until the shared state is ready.
    void wait() const
    {
        delegate_future_.wait();
    }

    // Wait for a specified relative time.
    template <class Rep, class Period>
    FutureStatus wait_for(const std::chrono::duration<Rep, Period>& timeout_duration) const
    {
        switch (delegate_future_.wait_for(timeout_duration))
        {
        case std::future_status::ready:
            return FutureStatus::ready;
        case std::future_status::timeout:
            return FutureStatus::timeout;
        default:
            assert(!"this std::future_status should not occur in our setup");
        }
    }

    // Wait until a specified absolute time.
    template <typename Clock, typename Duration>
    FutureStatus wait_until(const std::chrono::time_point<Clock, Duration>& deadline) const
    {
        switch (delegate_future_.wait_until(deadline))
        {
        case std::future_status::ready:
            return FutureStatus::ready;
        case std::future_status::timeout:
            return FutureStatus::timeout;
        default:
            assert(!"this std::future_status should not occur in our setup");
        }
    }

    // Set a continuation for when the shared state is ready
    template <typename F>
    auto then(F&& func) -> Future<decltype(func(std::move(*this)))>
    {
        std::unique_lock<std::mutex> lock(mutex_);
        
        using type = decltype(func(std::move(*this)));
        std::shared_ptr<Promise<type,E>> p = std::make_shared<Promise<type,E>>();
        Future<type> f = p->get_future();
        
        extra_state_->SetCallback([func,p,this](){
                p->set_value(func(std::move(*this)));
            });
//        if (is_ready()) {
//            extra_state_->FireCallback();
//        }
       
        return f;
    }

    // Return true only when the shared state is ready
    bool is_ready() const
    {
        return std::future_status::ready == delegate_future_.wait_for(std::chrono::seconds::zero());
    }

private:
    /**
     *
     * \private
     *
     * \brief Constructs a future from a given std::future and a pointer to the extra state that is shared with the
     * promise
     * \param delegate_future std::future that complies to C++11 and is used whenever functionality from C++11 is
     * needed.
     * \param extra_state State that is shared with its ara::core::Promise.
     */
    Future(std::future<R>&& delegate_future, internal::State::Ptr extra_state)
        : delegate_future_(std::move(delegate_future))
        , extra_state_(extra_state)
        , mutex_()
    {
    }

    std::future<R> delegate_future_;
    internal::State::Ptr extra_state_;
    std::mutex mutex_;
    template <typename, typename>
    friend class Promise;
};

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_FUTURE_H_
