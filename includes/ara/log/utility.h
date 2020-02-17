/***************************************************************************//**
 * @copyright Copyright (c) by Hinge-Tech R&D Center.
 * @file  utility.h
 * @brief utility header file.
 * @author Rimon Chen  
 * @version 01.00.00
 * @date  2019-07-05 
 * @par Description declare class LogManager\n
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
#ifndef LOGGINGUTILITY_H
#define LOGGINGUTILITY_H

#include <string>

namespace ara 
{
namespace log 
{
namespace internal 
{

/*! 
 *  @brief To be used whenever a DLT ID is requested, to avoid malformed naming.
 *  
 *  @param id the ID to be converted
 * 
 *  @return the string object of ID
 * 
 *  
 */
inline std::string dltId(const std::string& id) noexcept
{
    // substr usage might not be no-throw guaranteed - implementation not to be used for series SW
    return (!id.empty() ? id.substr(0, 4) : "NULL");
}

} // namespace internal
} // namespace log
} // namespace ara

#ifdef ENABLE_TEST_HELPER
    namespace testlogging 
    {
        /* @brief just for testing */
        struct TestHelper;
    }
    #define TEST_HELPER friend struct ::testlogging::TestHelper;
#else
    #define TEST_HELPER
#endif

#endif // LOGGINGUTILITY_H
