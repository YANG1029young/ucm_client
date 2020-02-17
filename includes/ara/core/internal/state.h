/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_CORE_INTERNAL_STATE_H_
#define ARA_CORE_INTERNAL_STATE_H_

#include <memory>
#include <mutex>

namespace ara
{
namespace core
{
namespace internal
{
/**
 * \brief Class State maintains the action (Set, Get,Fire or Execute) on callback
 *
 * \private
 */
class State
{
public:
    typedef std::shared_ptr<State> Ptr;
    State()
        :mutex_()
        ,called(false)
    {
    }
    virtual ~State()
    {
    }

    /**
     * \brief Executes the stored callback.
     *
     * \note The callback is never exposed outside this object so that no one may have a dangling pointer to the stored
     * callback.
     */
    void FireCallback()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (static_cast<bool>(callback_))
        {
            callback_();
        }
        else
        {
            called = true;
        }
    }

    template <typename F>
    /**
     * \brief Sets the callback.
     *
     * any callback that was set before is removed and replaced by the new callback.
     *
     * \param callback The callback to be set.
     */
    void SetCallback(F&& callback)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (called)
        {
            std::function<void(void)> f = std::forward<F>(callback);
            
            if (static_cast<bool>(f))
            {
                f();
            }
            
            called = false;
        }
        else
        {
            callback_ = std::forward<F>(callback);
        }
    }

private:
    std::function<void(void)> callback_;
    std::mutex mutex_;
    bool called;
};

} // namespace internal
} // namespace core
} // namespace ara

#endif // ARA_CORE_INTERNAL_STATE_H_
