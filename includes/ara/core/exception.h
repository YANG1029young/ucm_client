/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_CORE_EXCEPTION_H
#define ARA_CORE_EXCEPTION_H

#include <cstdint>
#include <stdexcept>
#include <map>
#include <sstream>

#include "ara/core/error_code.h"

namespace ara
{
namespace core
{

class Exception : std::exception
{
    ErrorCode const mErrorCode;

public:
    explicit Exception(ErrorCode&& err)
        : mErrorCode(std::move(err))
    {
    }

    ErrorCode const& Error() const noexcept
    {
        return mErrorCode;
    }

    char const* what() const noexcept override
    {
        return std::exception::what();
    }
    
    std::string toString()
    {
        std::stringstream ss;
        ss << "Exception: " << Error() << " (" << what() << ")";
        return ss.str();
    }
};

inline std::ostream& operator<<(std::ostream& out, Exception const& ex)
{
    return (out << "Exception: " << ex.Error() << " (" << ex.what() << ")");
}



///**
// * \brief Indicates errors that shall be delivered to the client in case an application error happens during method
// * call.
// *
// * Application errors are compatible to classic AUTOSAR errors and thus consist of a single byte value that indicates
// * the error. A server method may throw this exception to deliver this error code to the calling site. Currently this is
// * the only exception that is guaranteed to be transmitted to the calling site. All other exceptions may lead to
// * uncaught exceptions on server side and thus cause a terminate().
// */

//class ApplicationErrorException : public Exception
//{

//public:
//    /**
//     * \brief Default constructor that deliberately leaves the exception in an undefined state.
//     */
//    ApplicationErrorException()
//        : Exception("Application error")
//    {
//    }

//    /**
//     * \brief All subclassess of ApplicationErrorException shall override this method.
//     * The string returned by the overriden method shall have the following format:
//     * "<error> in <service interface> with ErrorCode: <error code>"
//     * where:
//     * <error> is the short name of the ApplicationError element within the ARXML model
//     * <service interface> is the fullyy qualified short name (short name path) of the service interface wherein
//     * the Application Error has been declared.
//     * <error code> the 6 bit error code defined within the ApplicationError element in decimal format.
//     * \return string representation of this ApplicationError (see above).
//     */

//    virtual const char* what() const noexcept override = 0;
//};

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_EXCEPTION_H
