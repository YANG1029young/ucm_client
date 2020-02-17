/***************************************************************************//**
 * @copyright Copyright (c) by Hinge-Tech R&D Center.
 * @file  logstream.h
 * @brief Head file for declaring class LogStream.
 * @author Rimon Chen  
 * @version 01.00.00
 * @date  2019-07-05 
 * @par Description declare the base of class LogStream for user\n
 * @par Others 
 * @par Function List
 *      1.
 *    
 * @par History:
 *      Date | Author| Modification
 *      -|-|-
 *      2019-07-17 | Rimon Chen | add new style of comment |
 *      2019-07-05 | Rimon Chen | create build this moudle |
 *     
 ******************************************************************************/
#ifndef ARA_LOG_LOGSTREAM_H__
#define ARA_LOG_LOGSTREAM_H__

#include <type_traits>

#include "ara/log/common.h"
#include "ara/log/logging.h"
namespace ara 
{
namespace log 
{

class Logger; /*!< forward declare Logger class */

/*!
 *  @brief The class LogStream represents a Log message, allowing stream operators to be
 *   used for appending data.
 * 
 *  @note Normally Application processes would not use this class directly. Instead one of
 *  the log methods provided in the main Logging API shall be used. Those methods
 *  automatically setup a temporary object of this class with the given log severity level.
 *  The only reason to use this class directly is, if the user wants to hold a LogStream
 *  object longer than the default one-statement scope. This is useful in order to create log
 *  messages that are distributed over multiple code lines. See the Flush() method for
 *  further information. Once this temporary object gets out of scope, its destructor takes
 *  care that the message buffer is ready to be processed by the Logging framework.
 * 
 *  Example:
 *  @code{.cpp}
 *   struct MyCustomType 
 *   {
 *       int8_t foo;
 *       ara::core::string bar;
 *   };
 *   
 *   LogStream& operator<<(LogStream& out, const MyCustomType& value)
 *   {
 *       return (out << value.foo << value.bar);
 *   }
 *
 *   // Producing the output "42 the answer is."
 *   Logger& ctx0 = CreateLogger("CTX0", "Context Description CTX0");
 *   ctx0.LogDebug () << MyCustomType{42, " the answer is."};
 *  @endcode
 */
class LogStream final
{
public:
	/*! 
     *  @brief Construct a LogStream.
	 *  
	 *  @details You can construct a LogStream .
	 *    But normally we create LogStream through Logger.
	 *
	 *  @see Logger
	 */
    LogStream();

	/*! 
     *  @brief Construct a LogStream.
	 *  
	 *  @details You can construct a LogStream .
	 *    But normally we create LogStream through Logger.
     * 
	 *  @param logLevel the level of log, see LogLevel
     *  @param logger the logger who owns this log stream, or who create this log stream
     * 
	 *  @see Logger,LogLevel
	 */
    LogStream(LogLevel logLevel, Logger& logger) noexcept;

    /*!
     *  @brief Destroying the stream object.
     *
     */
    ~LogStream();

    /*!
     *  @brief the copy constructor.
     *
     */
    LogStream(const LogStream&other);

    /*!
     *  @brief the overwritor of =.
     *
     */
    LogStream& operator=(const LogStream&other);

    /*!
     *  @brief the move constructor.
     *
     */
    LogStream(LogStream&&other);
    
    /*!
     *  @brief the overwritor of =.
     *
     */
    LogStream& operator=(LogStream&&other);

	/*! 
     *  @brief Sends out the current log buffer and initiates a new message stream.
	 *  
	 *  @details Calling Flush() is only necessary if the LogStream object is going to be re-used
     *  within the same scope. Otherwise, if the object goes out of scope (e.g. end of function
     *  block) then the flushing operation will be done internally by the destructor. 
     *  It is important to note that the Flush() command does not empty the buffer, 
     *  but it forwards the buffer’s current contents to the Logging framework.
	 *  
     *  @return None
	 */
    void Flush() noexcept;

	/*! 
     *  @brief Appends given value to the internal message buffer.
	 *  
     *  @param value to be appended to the internal message buffer
     * 
     *  @return LogStream&
     * 
     *  
	 */
    LogStream& operator<<(bool value) noexcept;

	/*! 
     *  @brief Appends given value to the internal message buffer.
	 *  
     *  @param value to be appended to the internal message buffer
     * 
     *  @return LogStream&
     * 
     *  
	 */
    LogStream& operator<<(uint8_t value) noexcept;

	/*! 
     *  @brief Appends given value to the internal message buffer.
	 *  
     *  @param value to be appended to the internal message buffer
     * 
     *  @return LogStream&
     * 
     *  
	 */
    LogStream& operator<<(uint16_t value) noexcept;

	/*! 
     *  @brief Appends given value to the internal message buffer.
	 *  
     *  @param value to be appended to the internal message buffer
     * 
     *  @return LogStream&
     * 
     *  
	 */
    LogStream& operator<<(uint32_t value) noexcept;

	/*! 
     *  @brief Appends given value to the internal message buffer.
	 *  
     *  @param value to be appended to the internal message buffer
     * 
     *  @return LogStream&
     * 
     *  
	 */
    LogStream& operator<<(uint64_t value) noexcept;

	/*! 
     *  @brief Appends given value to the internal message buffer.
	 *  
     *  @param value to be appended to the internal message buffer
     * 
     *  @return LogStream&
     * 
     *  
	 */
    LogStream& operator<<(int8_t value) noexcept;

	/*! 
     *  @brief Appends given value to the internal message buffer.
	 *  
     *  @param value to be appended to the internal message buffer
     * 
     *  @return LogStream&
     * 
     *  
	 */
    LogStream& operator<<(int16_t value) noexcept;

	/*! 
     *  @brief Appends given value to the internal message buffer.
	 *  
     *  @param value to be appended to the internal message buffer
     * 
     *  @return LogStream&
     * 
     *  
	 */
    LogStream& operator<<(int32_t value) noexcept;

	/*! 
     *  @brief Appends given value to the internal message buffer.
	 *  
     *  @param value to be appended to the internal message buffer
     * 
     *  @return LogStream&
     * 
     *  
	 */
    LogStream& operator<<(int64_t value) noexcept;

	/*! 
     *  @brief Appends given value to the internal message buffer.
	 *  
     *  @param value to be appended to the internal message buffer
     * 
     *  @return LogStream&
     * 
     *  
	 */
    LogStream& operator<<(float value) noexcept;

	/*! 
     *  @brief Appends given value to the internal message buffer.
	 *  
     *  @param value to be appended to the internal message buffer
     * 
     *  @return LogStream&
     * 
     *  
	 */
    LogStream& operator<<(double value) noexcept;

	/*! 
     *  @brief Appends given value to the internal message buffer.
	 *  
     *  @param value to be appended to the internal message buffer
     * 
     *  @return LogStream&
     * 
     *  
	 */
    LogStream& operator<<(const char* const value) noexcept;

	/*! 
     *  @brief Appends given value to the internal message buffer.
	 *  
     *  @param value to be appended to the internal message buffer
     * 
     *  @return LogStream&
     * 
     *  
	 */
    LogStream& operator<<(const LogRawBuffer& value) noexcept;

	/*! 
     *  @brief Appends given value to the internal message buffer.
	 *  
     *  @param value to be appended to the internal message buffer
     * 
     *  @return LogStream&
     * 
     *  
	 */
    LogStream& operator<<(const LogHex8& value) noexcept;

	/*! 
     *  @brief Appends given value to the internal message buffer.
	 *  
     *  @param value to be appended to the internal message buffer
     * 
     *  @return LogStream&
     * 
     *  
	 */
    LogStream& operator<<(const LogHex16& value) noexcept;

	/*! 
     *  @brief Appends given value to the internal message buffer.
	 *  
     *  @param value to be appended to the internal message buffer
     * 
     *  @return LogStream&
     * 
     *  
	 */
    LogStream& operator<<(const LogHex32& value) noexcept;

	/*! 
     *  @brief Appends given value to the internal message buffer.
	 *  
     *  @param value to be appended to the internal message buffer
     * 
     *  @return LogStream&
     * 
     *  
	 */
    LogStream& operator<<(const LogHex64& value) noexcept;

	/*! 
     *  @brief Appends given value to the internal message buffer.
	 *  
     *  @param value to be appended to the internal message buffer
     * 
     *  @return LogStream&
     * 
     *  
	 */
    LogStream& operator<<(const LogBin8& value) noexcept;


	/*! 
     *  @brief Appends given value to the internal message buffer.
	 *  
     *  @param value to be appended to the internal message buffer
     * 
     *  @return LogStream&
     * 
     *  
	 */
    LogStream& operator<<(const LogBin16& value) noexcept;

private:
    internal::LogReturnValue logRet_;  /*!< Inner log status */
    void *logLocalData_;   /*! context data buffer */
};

/*!
 *  @brief Support for LogStream objects as rvalue reference. Enables custom type <<operator overload as first call
 * 
 *  @tparam T The type of value
 *  @param out The log message stream
 *  @param value The data which will be write to LogStream
 *  @return the refrence of the current log message stream object
 */ 

template <typename T>
LogStream& operator<<(LogStream&& out, T&& value)  noexcept
{
    return (out << std::forward<T>(value));
}

/*!
 *  @brief Support for signed long long (transforms into int64_t on 64 bit platforms)
 * 
 *  @tparam T The type of value
 *  @param out The log message stream
 *  @param value The data which will be write to LogStream
 *  @return the refrence of the current log message stream object
 */ 
template <typename T = void,
          typename std::enable_if<((!std::is_same<long long, int64_t>::value) &&
                                     (sizeof(long long) == sizeof(int64_t))), T>::type* = nullptr>
inline LogStream& operator<<(LogStream& out, long long value) noexcept
{
    return (out << static_cast<int64_t>(value));
}

/*!
 *  @brief Support for signed long (transforms into int32_t on 32 bit platforms)
 * 
 *  @tparam T The type of value
 *  @param out The log message stream
 *  @param value The data which will be write to LogStream
 *  @return the refrence of the current log message stream object
 */ 
template <typename T = void,
          typename std::enable_if<((!std::is_same<long, int32_t>::value) &&
                                     (sizeof(long) == sizeof(int32_t))), T>::type* = nullptr>
inline LogStream& operator<<(LogStream& out, long value) noexcept
{
    return (out << static_cast<int32_t>(value));
}

/*!
 *  @brief Support for unsigned long long (transforms into uint64_t on 64 bit platforms)
 * 
 *  @tparam T The type of value
 *  @param out The log message stream
 *  @param value The data which will be write to LogStream
 *  @return the refrence of the current log message stream object
 */ 
template <typename T = void,
          typename std::enable_if<((!std::is_same<unsigned long long, uint64_t>::value) &&
                                     (sizeof(unsigned long long) == sizeof(uint64_t))), T>::type* = nullptr>
inline LogStream& operator<<(LogStream& out, unsigned long long value) noexcept
{
    return (out << static_cast<uint64_t>(value));
}

/*!
 *  @brief Support for unsigned long (transforms into uint32_t on 32 bit platforms)
 * 
 *  @tparam T The type of value
 *  @param out The log message stream
 *  @param value The data which will be write to LogStream
 *  @return the refrence of the current log message stream object
 */ 
template <typename T = void,
          typename std::enable_if<((!std::is_same<unsigned long, uint32_t>::value) &&
                                     (sizeof(unsigned long) == sizeof(uint32_t))), T>::type* = nullptr>
inline LogStream& operator<<(LogStream& out, unsigned long value) noexcept
{
    return (out << static_cast<uint32_t>(value));
}

/*!
 *  @brief Support for LogBin32 (transforms into 2 uint16_t on 32 bit platforms)
 * 
 *  @param out The log message stream
 *  @param value The data which will be write to LogStream
 *  @return the refrence of the current log message stream object
 */ 
inline LogStream& operator<<(LogStream& out, const LogBin32& value) noexcept
{
    /* Currently the Genivi DLT back-end does not natively support binary format >16 bit,
     * so we will split it up into multiple parts - as workaround */
    return out << LogBin16{static_cast<uint16_t>((value.value >> 16u) & 0x0000FFFFu)}
               << LogBin16{static_cast<uint16_t>(value.value & 0x0000FFFFu)};
}

/*!
 *  @brief Support for LogBin64 (transforms into 4 uint16_t on 32 bit platforms)
 * 
 *  @param out The log message stream
 *  @param value The data which will be write to LogStream
 *  @return the refrence of the current log message stream object
 */ 
inline LogStream& operator<<(LogStream& out, const LogBin64& value) noexcept
{
    /* Currently the Genivi DLT back-end does not natively support binary format >16 bit,
     * so we will split it up into multiple parts - as workaround */
    return out << LogBin16{static_cast<uint16_t>((value.value >> 48u) & 0x000000000000FFFFu)}
               << LogBin16{static_cast<uint16_t>((value.value >> 32u) & 0x000000000000FFFFu)}
               << LogBin16{static_cast<uint16_t>((value.value >> 16u) & 0x000000000000FFFFu)}
               << LogBin16{static_cast<uint16_t>(value.value & 0x000000000000FFFFu)};
}

/*!
 *  @brief Support for LogLevel (transforms into string)
 * 
 *  @param out The log message stream
 *  @param value The data which will be write to LogStream
 *  @return the refrence of the current log message stream object
 */ 
LogStream& operator<<(LogStream& out, LogLevel value) noexcept;

/*!
 *  @brief Support for uint32_t into LogHex32)
 * 
 *  @param value The data which will be write to LogStream
 *  @return the LogHex32 object
 */ 
constexpr LogHex32 loghex(uint32_t value) noexcept 
{ 
    return LogHex32{value}; 
}

/*!
 *  @brief Support for uint64_t into LogHex64)
 * 
 *  @param value The data which will be write to LogStream
 *  @return the LogHex64 object
 */ 
constexpr LogHex64 loghex(uint64_t value) noexcept 
{ 
    return LogHex64{value}; 
}

/*! 
 *  @brief Appends given value to the internal message buffer.
 *  
 *  @param out The log message stream
 *  @param value to be appended to the internal message buffer
 * 
 *  @return LogStream&
 * 
 *  
 */
inline LogStream& operator<<(LogStream& out, const void* const value) noexcept
{
    return (out << loghex(reinterpret_cast<std::uintptr_t>(value)));
}

/*! 
 *  @brief Appends given value to the internal message buffer.
 *  
 *  @param out The log message stream
 *  @param value to be appended to the internal message buffer
 * 
 *  @return LogStream&
 * 
 *  
 */
inline LogStream& operator<<(LogStream& out, const std::string& value) noexcept
{
    return (out << value.c_str());
}


} // namespace log
} // namespace ara

#endif // ARA_LOG_LOGSTREAM_H__
