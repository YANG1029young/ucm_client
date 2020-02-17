/***************************************************************************//**
 * @copyright Copyright (c) by Hinge-Tech R&D Center.
 * @file  object_document.h
 * @brief Head file for declaring class CObjectDocument.
 * @author Rimon Chen 
 * @version 01.00.00
 * @date  2019-06-27
 * @par Description declare class CObjectDocument
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
#ifndef JSCONFIG_OBJECT_DOCUMENT_H__
#define JSCONFIG_OBJECT_DOCUMENT_H__

#include <string>
#include <stack>

#include "jsconfig/common.h"
#include "jsconfig/object.h"

namespace jsconfig
{

/* predeclare private class CObjectDocument */
class CObjectDocumentPrivate;

/*!
 *  @brief json document class .
 *  
 *  @details this class can be used to parse json string or json file into CObject
 *  or save CObject into the specified file
 */
class JSCONFIG_API CObjectDocument
{
public:
    /*!
     *  @brief The constructor of CObjectDocument.
     *  
     *  @details default constructor 
     * 
     */
    CObjectDocument();

    /*!
     *  @brief The constructor of CObjectDocument.
     * 
     *  @param name unused 
     * 
     */
    CObjectDocument(std::string name);

    /*!
     *  @brief The destructor of CObjectDocument.
     * 
     *  @details delete all resource 
     *  in this document
     */
    ~CObjectDocument();

    /*!
     *  @brief parse the data in txt.
     * 
     *  the json string is given by txt 
     *  if there are some error, you can get error from errString when errstring != nullptr
     * 
     *  @param txt the json string data
     *  @param root the json object paring from txt
     *  @param errString error string where error infomations are saved
     * 
     *  @return true when it is successful, otherwise return false
     */
    static bool parseString(const char* txt, CObject& root, std::string *errString = nullptr);

    /*!
     *  @brief parse the data in txt.
     * 
     *  the json string is given by  txt 
     *  if there are some error, you can get error from errString when errstring != nullptr
     * 
     *  @param txt the json string data
     *  @param root the json object paring from txt
     *  @param errString error string where error infomations are saved
     * 
     *  @return true when it is successful, otherwise return false
     */
    static bool parseString(const std::string& txt, CObject& root, std::string *errString = nullptr);

    /*!
     *  @brief parse the data in file.
     * 
     *  the json file is given by filename
     *  if there are some error, you can get error from errString when errstring != nullptr
     * 
     *  @param filename save the file name of the file
     *  @param root the json object paring from txt
     *  @param errString error string where error infomations are saved
     * 
     *  @return true when it is successful, otherwise return false
     */
    static bool parse(std::string filename, CObject& root,
        std::string *errString = nullptr);

    /*!
     *   @brief save the root data in file.
     * 
     *   the file name is given by filename 
     *   if there are some error, you can get error from errString when errstring != nullptr
     * 
     *   @param filename save the file name of the file
     *   @param root the json object you want to save
     *   @param errString error string where error infomations are saved
     * 
     *   @return true when it is successful, otherwise return false
     */
    static bool save(std::string filename, CObject& root,
        std::string *errString = nullptr);

    /*!
     *  @brief parse data in txt.
     * 
     *  the json context is given by txt 
     *  when there are some error, you can get error from errorString
     *  
     *  @see std::string errorString();
     * 
     *  @param txt parse the file name of the file
     * 
     *  @return true when it is successful, otherwise return false
     */
    bool parseString(const char* txt);

    /*!
     *  @brief parse data in txt.
     * 
     *  the json context is given by txt 
     *  when there are some error, you can get error from errorString
     *  
     *  @see std::string errorString();
     * 
     *  @param txt parse the file name of the file
     * 
     *  @return true when it is successful, otherwise return false
     */
    bool parseString(const std::string& txt);

    /*!
     *  @brief parse data in file.
     * 
     *  the file name is given by filename 
     *  when there are some error, you can get error from errorString
     *  
     *  @see std::string errorString();
     * 
     *  @param filename parse the file name of the file
     * 
     *  @return true when it is successful, otherwise return false
     */
    bool parse(std::string filename);

    /*!
     *  @brief save data in file.
     * 
     *  the file name is given by filename 
     *  when there are some error, you can get error from errorString
     *  
     *  @see std::string errorString();
     * 
     *  @param filename save the file name of the file
     * 
     *  @return true when it is successful, otherwise return false
     */
    bool save(std::string filename);

    /*!
     *  @brief get the error string that descripts the parsing error.
     * 
     *  when there are some error in json file, otherwise return empty string
     * 
     *  @return the error string
     */
    std::string errorString();

    /*!
     *  @brief get the document's data pointer.
     * 
     *  get data pointer from class CObjectDocument, the
     *  point you get should not be delete by user. it is different
     *  from member function 
     *  
     *  @see CObject* dispatch()
     * 
     *  @return root object pointer
     *   -  object pointer if success
     *   -  nullptr if fail
     *  @note the living time is managed by the instance of CObjectDocument
     */
    CObject* root();

    /*!
     *  @brief get the document's data pointer and dispatch.
     * 
     *  get data pointer from class CObjectDocument, root object owner tranlate to user
     *  so user should delete the root object when the root can not be used anymore
     *  from member function 
     *  
     *  @see CObject* root();
     * 
     *  @return root object pointer
     *   -  object pointer if success
     *   -  nullptr if fail
     * 
     *  @note the living time is managed by user
     */
    CObject* dispatch();

private:
    CObjectDocumentPrivate* m_data;    /*!< @details the private implement data of CObjectDocument */
};

} // jsconfig

#endif // JSCONFIG_OBJECT_DOCUMENT_H__
