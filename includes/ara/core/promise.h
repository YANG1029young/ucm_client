/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_CORE_PROMISE_H_
#define ARA_CORE_PROMISE_H_

#include <exception>
#include <future>
#include <mutex>

#include "internal/state.h"
#include "future.h"

namespace ara
{
namespace core
{

template <class T, typename E = ErrorCode>
/**
 *  \brief Promise class is an ara::core specific promise interface to store a value or exception that is later retrieved
 *  asynchronously by ara::core::Future
 *
 *  The interface to this promise is taken from std::promise
 */
class Promise
{
    using R = Result<T, E>;

public:
    Promise()
        : extra_state_(std::make_shared<internal::State>())
        , mutex_()
    {
    }

    ~Promise()
    {
    }

    // not copyable
    Promise(Promise const&) = delete;
    Promise& operator=(Promise const&) = delete;

    // movable
    Promise(Promise<T>&& other)
        : delegate_promise_(std::move(other.delegate_promise_))
        , extra_state_(std::move(other.extra_state_))
        , mutex_()
    {
    }
    
    Promise& operator=(Promise<T>&& other)
    {
        delegate_promise_ = std::move(other.delegate_promise_);
        extra_state_ = std::move(other.extra_state_);
        return *this;
    }

    /**
     * \brief Returns an associated future of type T.
     *
     * The returned future is set as soon as this promise receives the result or an exception. This method must only be
     * called once as it is not allowed to have multiple futures per promise.
     *
     * \return ara::core::Future of type T.
     */
    ara::core::Future<T> get_future()
    {
        return ara::core::Future<T>(delegate_promise_.get_future(), extra_state_);
    }

    void SetError(E&& err)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        R r = R::template FromError(std::move(err));
        delegate_promise_.set_value(r);
        extra_state_->FireCallback();
    }
    
    void SetError(E const &err)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        R r = R::template FromError(err);
        delegate_promise_.set_value(r);
        extra_state_->FireCallback();
    }

    /**
     * \brief Sets an exception.
     *
     * Calling get() on the associated future will rethrow the exception in the context the future's method was called
     * in.
     *
     * \param p Exception pointer to set
     */
    void set_exception(std::exception_ptr p)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        delegate_promise_.set_exception(p);
        extra_state_->FireCallback();
    }
    /**
     * \brief Move the result into the future.
     *
     * \param value Value to store.
     */
    void set_value(T&& value)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        delegate_promise_.set_value(value);
        extra_state_->FireCallback();
    }
    /**
     * \brief Copy result into the future.
     *
     * \param value Value to store.
     */
    void set_value(const T& value)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        delegate_promise_.set_value(value);
        extra_state_->FireCallback();
    }

private:
    std::promise<R> delegate_promise_;
    internal::State::Ptr extra_state_;
    std::mutex mutex_;
};

/**
 * Explicit specialization for void
 */
template <typename E>
class Promise<void, E>
{
    using R = Result<void, E>;

public:
    Promise()
        : extra_state_(std::make_shared<internal::State>())
        , mutex_()
    {
    }
    ~Promise()
    {
    }

    // not copyable
    Promise(Promise const&) = delete;
    Promise& operator=(Promise const&) = delete;

    // movable
    Promise(Promise<void>&& other) noexcept
        : delegate_promise_(std::move(other.delegate_promise_))
        , extra_state_(std::move(other.extra_state_))
        , mutex_()
    {
    }
    
    Promise& operator=(Promise<void>&& other) noexcept
    {
        delegate_promise_ = std::move(other.delegate_promise_);
        extra_state_ = std::move(other.extra_state_);
        return *this;
    }

    /**
     * \brief Returns an associated future of type T.
     *
     * The returned future is set as soon as this promise receives the result or an exception. This method must only be
     * called once as it is not allowed to have multiple futures per promise.
     *
     * \return ara::core::Future of type T.
     */
    ara::core::Future<void> get_future()
    {
        return ara::core::Future<void>(delegate_promise_.get_future(), extra_state_);
    }
    
    void SetError(E&& err)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        R r = R::template FromError(std::move(err));
        delegate_promise_.set_value(r);
        extra_state_->FireCallback();
    }
    
    void SetError(E const &err)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        R r = R::template FromError(err);
        delegate_promise_.set_value(r);
        extra_state_->FireCallback();
    }

    /**
     * \brief Sets an exception.
     *
     * Calling get() on the associated future will rethrow the exception in the context the future's method was called
     * in.
     *
     * \param p Exception pointer to set
     */
    void set_exception(std::exception_ptr p)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        delegate_promise_.set_exception(p);
        extra_state_->FireCallback();
    }

    /**
     * \brief Copy result into the future.
     *
     * \param value Value to store.
     */
    void set_value()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        R r = R::FromValue();
        delegate_promise_.set_value(r);
        extra_state_->FireCallback();
    }

private:
    std::promise<R> delegate_promise_;
    internal::State::Ptr extra_state_;
    std::mutex mutex_;
};

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_PROMISE_H_
