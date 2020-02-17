/***************************************************************************//**
 * @copyright Copyright (c) by Hinge-Tech R&D Center.
 * @file  common.h
 * @brief Head file for declaring enum class.
 * @author Rimon Chen  
 * @version 01.00.00
 * @date  2019-07-05 
 * @par Description
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

#ifndef ARALOGCOMMON_H__
#define ARALOGCOMMON_H__

#include <memory>

namespace ara 
{
namespace log 
{

/*!
 *  @brief  List of possible severity levels .  
 */
enum class LogLevel : uint8_t 
{
  kOff      = 0x00, ///< No logging
  kFatal    = 0x01, ///< Fatal error, not recoverable
  kError    = 0x02, ///< Error with impact to correct functionality
  kWarn     = 0x03, ///< Warning if correct behavior cannot be ensured
  kInfo     = 0x04, ///< Informational, providing high level understanding
  kDebug    = 0x05, ///< Detailed information for programmers
  kVerbose  = 0x06  ///< Extra-verbose debug messages (highest grade of information)
};

/*!
 *  @brief  Log mode. Flags, used to configure the sink for log messages.
 *  @details  In order to combine flags, at least the OR and AND operators
 *      needs to be provided for this type.
 */
enum class LogMode : uint8_t 
{
  kRemote   = 0x01,  ///< Sent remotely
  kFile     = 0x02,  ///< Save to file
  kConsole  = 0x04   ///< Forward to console
};


namespace internal 
{

/*!
 *  @brief  Log return value define.
 */
enum class  LogReturnValue : int8_t 
{
    kReturnLoggingDisabled  = -7,
    kReturnUserBufferFull   = -6,
    kReturnWrongParameter   = -5,
    kReturnBufferFull       = -4,
    kReturnPipeFull         = -3,
    kReturnPipeError        = -2,
    kReturnError            = -1,
    kReturnOk               = 0,
    kReturnTrue             = 1
};

}; // namespace internal

/*!
 *  @brief  operator or for LogMode.
 *  @param lhs left value
 *  @param rhs right value
 *  @return the result of lhs|rhs
 */
inline LogMode operator|(LogMode lhs, LogMode rhs)
{
    return (static_cast<LogMode>(static_cast<typename std::underlying_type<LogMode>::type>(lhs) |
                                 static_cast<typename std::underlying_type<LogMode>::type>(rhs)));
}

/*!
 *  @brief  operator |= for LogMode.
 *  @param lhs left value
 *  @param rhs right value
 *  @return the result of lhs|rhs
 */
inline LogMode operator|=(LogMode lhs, LogMode rhs)
{
    return (static_cast<LogMode>(static_cast<typename std::underlying_type<LogMode>::type>(lhs) |
                                 static_cast<typename std::underlying_type<LogMode>::type>(rhs)));
}

/*!
 *  @brief  operator and for LogMode.
 *  @param lhs left value
 *  @param rhs right value
 *  @return the result of lhs&rhs
 */
inline typename std::underlying_type<LogMode>::type operator&(LogMode lhs, LogMode rhs)
{
    return (static_cast<typename std::underlying_type<LogMode>::type>(lhs) &
            static_cast<typename std::underlying_type<LogMode>::type>(rhs));
}

/*!
 *  @brief  operator &= for LogMode.
 *  @param lhs left value
 *  @param rhs right value
 *  @return the result of lhs&rhs
 */
inline typename std::underlying_type<LogMode>::type operator&=(LogMode lhs, LogMode rhs)
{
    return (static_cast<typename std::underlying_type<LogMode>::type>(lhs) &
            static_cast<typename std::underlying_type<LogMode>::type>(rhs));
}

/// @}
} /* namespace log */
} /* namespace ara */

#endif  // ARALOGCOMMON_H__
