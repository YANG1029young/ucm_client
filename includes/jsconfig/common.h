/***************************************************************************//**
 * @copyright Copyright (c) by Hinge-Tech R&D Center.
 * @file  common.h
 * @brief Head file for comomon enums or defines.
 * @author Rimon Chen 
 * @version 01.00.00
 * @date  2019-06-27
 * @par Description define the api export macro and enum ObjectType and the macro of separator path in json
 * @par Others 
 * @par Function List
 *      1. 
 *    
 * @par History:
 *      Date | Author| Modification
 *      -|-|-
 *      2019-07-27 | Rimon Chen | add new style of comment |
 *      2019-06-27 | Rimon Chen | create                   |
 *     
 ******************************************************************************/
#ifndef JSCONFIG_COMMON_H__
#define JSCONFIG_COMMON_H__

#ifdef JSCONFIG_LIB

#ifdef _WIN32
/*! declare API/API class macro for windows */
#define JSCONFIG_API __declspec(dllexport)
#else
/*! declare API/API class macro for unix-like  */
#define JSCONFIG_API __attribute__((visibility("default")))
#endif // _WIN32

#else

#ifdef _WIN32
/*! declare API/API class macro for windows*/
#define JSCONFIG_API __declspec(dllimport)
#else
/*! declare API/API class macro for unix-like */
#define JSCONFIG_API __attribute__((visibility("default")))
#endif // _WIN32

#endif // JSCONFIG_LIB

namespace jsconfig
{

/*!
 *   @brief the enum type of Objects.
 *   
 *   define all types of the objects,
 *   each type represents a kind of node in json
 */
typedef enum
{
    kInvalid = 0,     /*!< the type of object's value is invalid, for validation */
    kBool,            /*!< the type of object's value is boolean */
    kNull,            /*!< the type of object's value is null */
    kUInt64,          /*!< the type of object's value is uint64_t */
    kInt64,           /*!< the type of object's value is int64_t*/
    kDouble,          /*!< the type of object's value is double */
    kString,          /*!< the type of object's value is string */
    kArray,           /*!< the type of object's value is array(following []) */
    kObject,          /*!< the type of object's value is object(following {}) */
}ObjectType;


/*! @brief the spepertor of path in json finding function group */
#define PATH_SEP "/"

} // jsconfig


#endif // JSCONFIG_COMMON_H__
