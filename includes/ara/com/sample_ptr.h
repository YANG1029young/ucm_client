/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_SAMPLE_PTR_H_
#define ARA_COM_SAMPLE_PTR_H_

#include "ara/com/e2e/state_machine.h"
#include <memory>

namespace ara
{
namespace com
{

template <typename T>
class SamplePtr
{
    using E2ECheckStatus = ara::com::E2E_state_machine::E2ECheckStatus;

    std::shared_ptr<T> m_dataPtr;
    E2ECheckStatus m_e2eCheckStatus;

public:
    /* constexpr shared_ptr() noexcept */
    explicit constexpr SamplePtr(E2ECheckStatus e2eCheckStatus = E2ECheckStatus::Ok) noexcept
        : m_dataPtr()
        , m_e2eCheckStatus(e2eCheckStatus)
    {
    }

    /* template<class Y>shared_ptr(Y* ptr) ctor can throw */
    explicit SamplePtr(T* ptr, E2ECheckStatus e2eCheckStatus = E2ECheckStatus::Ok)
        : m_dataPtr(ptr)
        , m_e2eCheckStatus(e2eCheckStatus)
    {
    }

    /* shared_ptr( const shared_ptr& r ) noexcept; */
    SamplePtr(const SamplePtr<T>& r) noexcept
        : m_dataPtr(r.m_dataPtr)
        , m_e2eCheckStatus(r.m_e2eCheckStatus)
    {
    }

    /* shared_ptr( const shared_ptr&& r ) noexcept; */
    SamplePtr(SamplePtr<T>&& r) noexcept
        : m_dataPtr(std::move(r.m_dataPtr))
        , m_e2eCheckStatus(std::move(r.m_e2eCheckStatus))
    {
    }

    /* shared_ptr& operator=( const shared_ptr& r ) noexcept; */
    SamplePtr& operator=(const SamplePtr<T>& r) noexcept
    {
        m_dataPtr = r.m_dataPtr;
        m_e2eCheckStatus = r.m_e2eCheckStatus;
        return *this;
    }

    /* shared_ptr& operator=( shared_ptr&& r ) noexcept; */
    SamplePtr& operator=(SamplePtr<T>&& r) noexcept
    {
        m_dataPtr = std::move(r.m_dataPtr);
        m_e2eCheckStatus = std::move(r.m_e2eCheckStatus);
        return *this;
    }

    /* T& shared_ptr::operator*() const noexcept; */
    T& operator*() const noexcept
    {
        return m_dataPtr.operator*();
    }

    /* T* shared_ptr::operator->() const noexcept; */
    T* operator->() const noexcept
    {
        return m_dataPtr.operator->();
    }
    
    explicit operator bool() const noexcept
    {
        return m_dataPtr.operator bool();
    }
    
    void Swap(SamplePtr& r) noexcept
    {
        E2ECheckStatus status = r.m_e2eCheckStatus;
        r.m_e2eCheckStatus = m_e2eCheckStatus;
        m_e2eCheckStatus = status;
        
        m_dataPtr.swap(r.m_dataPtr);
        
    }
    
    void Reset(T* ptr)
    {
        m_dataPtr.reset(ptr);
    }
    
    T* Get () const noexcept
    {
        return m_dataPtr.get();
    }
    
    long UseCount () const noexcept
    {
        return m_dataPtr.use_count();
    }

    E2ECheckStatus GetE2ECheckStatus() const noexcept
    {
        return m_e2eCheckStatus;
    }
};

template <typename T, typename... Args>
SamplePtr<T> make_sample_ptr(Args&&... args)
{
    return SamplePtr<T>(new T(std::forward<Args>(args)...));
}

} // com
} // ara

#endif // ARA_COM_SAMPLE_PTR_H_
