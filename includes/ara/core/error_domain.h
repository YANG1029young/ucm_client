/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_CORE_ERROR_DOMAIN_H_
#define ARA_CORE_ERROR_DOMAIN_H_

#include <cstdint>
#include <exception>

namespace ara
{
namespace core
{

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#endif

// forward declaration
class ErrorCode;

class ErrorDomain
{
public:
    using IdType = std::uint64_t;
    using CodeType = std::int32_t;
    using SupportDataType = std::int32_t;

    ErrorDomain(ErrorDomain const&) = delete;
    ErrorDomain(ErrorDomain&&) = delete;
    ErrorDomain& operator=(ErrorDomain const&) = delete;
    ErrorDomain& operator=(ErrorDomain&&) = delete;

    virtual char const* Name() const noexcept = 0;

    virtual char const* Message(CodeType errorCode) const noexcept = 0;

    /**
     * @brief Throws the given errorCode as Exception
     * @param errorCode error code to be thrown
     * @remark if ARA_NO_EXCEPTIONS is defined, this function call will terminate.
     */
    [[noreturn]] virtual void ThrowAsException(ErrorCode const& errorCode) const noexcept(false) = 0;

    constexpr IdType Id() const noexcept
    {
        return mId;
    }

    constexpr bool operator==(ErrorDomain const& other) const noexcept
    {
        return mId == other.mId;
    }

    constexpr bool operator!=(ErrorDomain const& other) const noexcept
    {
        return mId != other.mId;
    }

protected:
    constexpr explicit ErrorDomain(IdType id) noexcept
        : mId(id)
    {
    }

    // This dtor is non-virtual (and trivial) so that this class is a literal type.
    // While we do have virtual functions, we never need polymorphic destruction.
    ~ErrorDomain() = default;

private:
    IdType const mId;
};

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_ERROR_DOMAIN_H_
