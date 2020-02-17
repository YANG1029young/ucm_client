/***************************************************************************//**
 * @copyright Copyright (c) by Hinge-Tech R&D Center.
 * @file  logger.h
 * @brief Head file for declaring class Logger.
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
#ifndef ARA_LOG_LOGGER_H__
#define ARA_LOG_LOGGER_H__

#include <atomic>
#include <map>
#include <string>

#include "ara/log/common.h"
#include "ara/log/logstream.h"

namespace ara 
{
namespace log 
{

/*!
 *  @brief  The class Logger represents a logger context. 
 *  
 *  @details The Logging framework defines contexts which can be seen as
 *   logger instances within one Application process or process scope.
 *   The contexts have the following properties:\n
 *    1) Context ID\n
 *    2) Description of the Context ID\n
 *    3) Default log level
 * 
 *    A context will be automatically registered against the Logging back-end during creation phase, 
 *    as well as automatically deregistered during process shutdown phase.
 *    So the end user does not care for the objects life time. To ensure such housekeeping
 *    functionality, a strong ownership of the logger instances needs to be ensured towards
 *    the Logging framework. This means that the Application process are not
 *    supposed to call the Logger constructor themselves.
 *    The user is not allowed to create a Logger object by himself. Logger context needs to
 *    be created by the provided API call CreateLogger(). This is because the internal
 *    LogManager is tracking all created log contexts and does the checking of correct ID
 *    naming conventions as well as multiple instantiation attemp
 */
class Logger final
{
public:
	/*! 
     *  @brief Construct a logger context.
	 *  
	 *  @details You can construct a Logger by giving context id , context description and default log loevel.
	 *    But normally we use CreateLogger to create logger context.
	 *
	 *  @param ctxId the ID of logger context
     *  @param ctxDescription the ID of logger conext description
     *  @param ctxDefLogLevel the default log loevel
	 *  
	 *  @see ara::log::CreateLogger
	 */
    Logger(const std::string& ctxId, const std::string& ctxDescription, LogLevel ctxDefLogLevel);

	/*! 
     *  @brief Destruct a logger context.
	 *  
	 *  @details It will release the back-end resource of logger context, not only the instances of Logger::Impl
     *  but also the instances of LoggStream. But you do not warry that  The lifetime of the Logger is shorter than the Logstream's
	 *
	 */
    ~Logger();

	/*! 
     *  @brief Create a LogStream object for FATAL messages. 
	 *  
	 *  @details The returned object will accept arguments via
     *   the insert stream operator "«".
     * 
     *   In the normal usage scenario, the object’s life time of the created LogStream is scoped within
     *   one statement (ends with ; after last passed argument). If one wants to extend the LogStream
     *   object’s life time, the object might be assigned to a named variable. Refer to the LogStream
     *   class documentation for further details.
	 *  
     *  @return LogStream object of FATAL severity.
     * 
     *  @note In the normal usage scenario, the object’s life time of the created LogStream is scoped within
     *   one statement (ends with ; after last passed argument). If one wants to extend the LogStream
     *   object’s life time, the object might be assigned to a named variable.
	 */
    LogStream LogFatal() noexcept;

	/*! 
     *  @brief Create a LogStream object for ERROR messages. 
	 *  
	 *  @details The returned object will accept arguments via
     *   the insert stream operator "«".
     * 
     *   In the normal usage scenario, the object’s life time of the created LogStream is scoped within
     *   one statement (ends with ; after last passed argument). If one wants to extend the LogStream
     *   object’s life time, the object might be assigned to a named variable. Refer to the LogStream
     *   class documentation for further details.
	 *  
     *  @return LogStream object of ERROR severity.
     * 
     *  @note In the normal usage scenario, the object’s life time of the created LogStream is scoped within
     *   one statement (ends with ; after last passed argument). If one wants to extend the LogStream
     *   object’s life time, the object might be assigned to a named variable.
	 */
    LogStream LogError() noexcept;

	/*! 
     *  @brief Create a LogStream object for WARN messages. 
	 *  
	 *  @details The returned object will accept arguments via
     *   the insert stream operator "«".
     * 
     *   In the normal usage scenario, the object’s life time of the created LogStream is scoped within
     *   one statement (ends with ; after last passed argument). If one wants to extend the LogStream
     *   object’s life time, the object might be assigned to a named variable. Refer to the LogStream
     *   class documentation for further details.
	 *  
     *  @return LogStream object of WARN severity.
     * 
     *  @note In the normal usage scenario, the object’s life time of the created LogStream is scoped within
     *   one statement (ends with ; after last passed argument). If one wants to extend the LogStream
     *   object’s life time, the object might be assigned to a named variable.
	 */
    LogStream LogWarn() noexcept;

	/*! 
     *  @brief Create a LogStream object for INFO messages. 
	 *  
	 *  @details The returned object will accept arguments via
     *   the insert stream operator "«".
     * 
     *   In the normal usage scenario, the object’s life time of the created LogStream is scoped within
     *   one statement (ends with ; after last passed argument). If one wants to extend the LogStream
     *   object’s life time, the object might be assigned to a named variable. Refer to the LogStream
     *   class documentation for further details.
	 *  
     *  @return LogStream object of INFO severity.
     * 
     *  @note In the normal usage scenario, the object’s life time of the created LogStream is scoped within
     *   one statement (ends with ; after last passed argument). If one wants to extend the LogStream
     *   object’s life time, the object might be assigned to a named variable.
	 */
    LogStream LogInfo() noexcept;

	/*! 
     *  @brief Create a LogStream object for DEBUG messages. 
	 *  
	 *  @details The returned object will accept arguments via
     *   the insert stream operator "«".
     * 
     *   In the normal usage scenario, the object’s life time of the created LogStream is scoped within
     *   one statement (ends with ; after last passed argument). If one wants to extend the LogStream
     *   object’s life time, the object might be assigned to a named variable. Refer to the LogStream
     *   class documentation for further details.
	 *  
     *  @return LogStream object of DEBUG severity.
     * 
     *  @note In the normal usage scenario, the object’s life time of the created LogStream is scoped within
     *   one statement (ends with ; after last passed argument). If one wants to extend the LogStream
     *   object’s life time, the object might be assigned to a named variable.
	 */
    LogStream LogDebug() noexcept;

	/*! 
     *  @brief Create a LogStream object for VERBOSE messages. 
	 *  
	 *  @details The returned object will accept arguments via
     *   the insert stream operator "«".
     * 
     *   In the normal usage scenario, the object’s life time of the created LogStream is scoped within
     *   one statement (ends with ; after last passed argument). If one wants to extend the LogStream
     *   object’s life time, the object might be assigned to a named variable. Refer to the LogStream
     *   class documentation for further details.
	 *  
     *  @return LogStream object of VERBOSE severity.
     * 
     *  @note In the normal usage scenario, the object’s life time of the created LogStream is scoped within
     *   one statement (ends with ; after last passed argument). If one wants to extend the LogStream
     *   object’s life time, the object might be assigned to a named variable.
	 */
    LogStream LogVerbose() noexcept;

	/*! 
     *  @brief Ask for when this Logger will ouput messages for the specified log loevel;
	 *  
     *  @return Return whether this Logger will output messages for the specified log level.
     *   - true if this Logger will output messages
     *   - false if this Logger will not output messages
	 */
    bool IsLogEnabled(LogLevel logLevel) const noexcept;

	/*! 
     *  @brief Unregister Logger context from back-end;
     * 
	 */
    void unregisterBackends() noexcept;

	/*! 
     *  @brief Get the logger context from back-end
     *  @return Return the pointer of logger context from back-end.
     *   - non-pointer if this Logger is initiated rightly
     *   - nullptr otherwise
	 */
    void* getContext();

	/*! 
     *  @brief get the ID of Logger context.
     * 
     *  @details The length of ID isn't greate than 4
	 *  
     *  @return Return the ID of Logger context
	 */
    std::string getId() const noexcept;

	/*! 
     *  @brief Output log text by using Logger directly.
     * 
     *  @details You can output string logs by using specified log level
	 *  
	 */
    void syslog(LogLevel loglv, const std::string& str);

	/*! 
     *  @brief Output log text by using Logger  directly.
     * 
     *  @details You can output string logs by using specified log level
     *   according to a format as printf
	 *  
	 */
    void syslog(LogLevel loglv, const char* fmt,...);

private:
    class Impl;                  /*!<  @brief The implement class of Logger */
    std::unique_ptr<Impl> pImpl; /*!<  @brief the instance of Logger */

private:
    std::map<LogLevel, LogStream*> m_logstreams;    /*!<   @brief The LogStream object owned by this Logger*/
};

} /* namespace log */
} /* namespace ara */

#endif // ARA_LOG_LOGGER_H__
