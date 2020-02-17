/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_CORE_ERROR_CODE_H_
#define ARA_CORE_ERROR_CODE_H_

#include "ara/core/error_domain.h"

#include <ostream>
#include <cstdint>

namespace ara
{
namespace core
{

class ErrorCode
{
    friend std::ostream& operator<<(std::ostream& out, ErrorCode const& e)
    {
        return (out << e.mDomain->Name() << ":" << e.mValue << ":" << e.mSupportData << ":"
                    << (e.mUserMessage ? e.mUserMessage : ""));
    }

    using CodeType = ErrorDomain::CodeType;
    using SupportDataType = ErrorDomain::SupportDataType;

public:
    template <typename EnumT, typename = typename std::enable_if<std::is_enum<EnumT>::value>::type>
    constexpr ErrorCode(EnumT e, SupportDataType data = 0, char const* userMessage = nullptr) noexcept
        // Call MakeErrorCode() unqualified, so the correct overload is found via ADL.
        : ErrorCode(MakeErrorCode(e, data, userMessage))
    {
    }

    template <typename EnumT, typename = typename std::enable_if<std::is_enum<EnumT>::value>::type>
    constexpr ErrorCode(EnumT e, char const* userMessage, SupportDataType data = 0) noexcept
        // Call MakeError() unqualified, so the correct overload is found via ADL.
        : ErrorCode(MakeErrorCode(e, data, userMessage))
    {
    }

    constexpr ErrorCode(CodeType value,
        ErrorDomain const& domain,
        SupportDataType data = 0,
        char const* userMessage = nullptr) noexcept
        : mValue(value)
        , mSupportData(data)
        , mDomain(&domain)
        , mUserMessage(userMessage)
    {
    }

    constexpr CodeType Value() const noexcept
    {
        return mValue;
    }

    constexpr SupportDataType SupportData() const noexcept
    {
        return mSupportData;
    }

    constexpr ErrorDomain const& Domain() const noexcept
    {
        return *mDomain;
    }

    constexpr char const* UserMessage() const noexcept
    {
        return mUserMessage;
    }

    char const* Message() const noexcept
    {
        return Domain().Message(Value());
    }

    [[noreturn]] void ThrowAsException() const noexcept(false)
    {
        Domain().ThrowAsException(*this);

        // Never reached, but apparently needed to avoid warnings from certain compilers (such as 5.4.0).
        std::terminate();
    }

private:
    CodeType mValue;
    SupportDataType mSupportData;
    ErrorDomain const* mDomain;  // non-owning pointer to the associated ErrorDomain
    char const* mUserMessage;  // non-owning pointer to a static, null-terminated string
};

constexpr inline bool operator==(ErrorCode const& lhs, ErrorCode const& rhs)
{
    return lhs.Domain() == rhs.Domain() && lhs.Value() == rhs.Value();
}

constexpr inline bool operator!=(ErrorCode const& lhs, ErrorCode const& rhs)
{
    return lhs.Domain() != rhs.Domain() || lhs.Value() != rhs.Value();
}

template <typename ExceptionType>
void ThrowOrTerminate(ErrorCode errorCode)
{
#ifndef ARA_NO_EXCEPTIONS
    throw ExceptionType(std::move(errorCode));
#else
    (void)errorCode;
    std::terminate();
#endif
}

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_ERROR_CODE_H_
