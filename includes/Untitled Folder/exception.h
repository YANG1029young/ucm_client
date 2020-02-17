/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_EXCEPTION_H_
#define ARA_COM_EXCEPTION_H_

#include <cstdint>
#include <stdexcept>

namespace ara
{
namespace com
{


class Exception : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class ApplicationErrorException : public Exception
{
public:
    ApplicationErrorException()
        : Exception("Application error")
    {
    }

    virtual const char* what() const noexcept override = 0;
};

}  // namespace com
}  // namespace ara

#endif  // ARA_COM_EXCEPTION_H_
