/***************************************************************************//**
 * @copyright Copyright (c) by Hinge-Tech R&D Center.
 * @file  object.h
 * @brief Head file for declaring class CObject.
 * @author Rimon Chen 
 * @version 01.00.00
 * @date  2019-06-27
 * @par Description declare class CObject
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
#ifndef JSCONFIG_OBJECT_H__
#define JSCONFIG_OBJECT_H__

#include <string>
#include <stdint.h>

#include "jsconfig/common.h"
#include "jsconfig/object_array.h"

namespace jsconfig
{

/*!
 *  @brief json object class .
 *  
 *  @details this class can be used to represend every object in json file,
 *  every object contain the key and value. 
 *  the value includes the string, the number etc.
 */
class JSCONFIG_API CObject
{
public:
    /*!
     *  @brief the default constructor of CObject.
     * 
     *  @details If you  create an instance of CObject by using this
     *  default constructor, you will get a variant object 
     *  whiches type is kInvalid, without no name.
     *  In this situation, it is not meaningful to get its value
     */
    CObject();

    /*!
     *  @brief the overwrite constructor of CObject.
     * 
     *  @details If you  create an instance of CObject by using this
     *  overwrite constructor, you will get a variant object 
     *  whiches type is asigned by param type, without no name.
     *  In this situation, its value is set zero, 0(or 0.0) according
     *   to kInt64/kUInt64, false according to kBool, and so on.
     * 
     *  @param type the type of json object
    */
    CObject(ObjectType type);

    /*!
     *  @brief the overwrite constructor of CObject,.
     * 
     *  @details The name is given by c string pointer.
     *  If you  create an instance of CObject by using this
     *  overwrite constructor, you will get a variant object 
     *  whiches type is asigned by param type, with the name is asigned by param name.
     *  In this situation, its value is set zero, 0(or 0.0) according 
     *  to kInt64/kUInt64, false according to kBool, and so on.
     * 
     *  @param type the type of json object
     *  @param name the name of json object(also call key of key-value)
     * 
     */
    CObject(ObjectType type, const char* name);
    
    /*!
     *  @brief the overwrite constructor of CObject.
     * 
     *  @details The is given by cpp string object refrence
     *  If you  create an instance of CObject by using this
     *  overwrite constructor, you will get a variant object 
     *  whiches type is asigned by param type, with the name is asigned by param name.
     *  In this situation, its value is set zero, 0(or 0.0) according 
     *  to kInt64/kUInt64, false according to kBool, and so on.
     * 
     *  @param type the type of json object
     *  @param name the name of json object(also call key of key-value)
     */
    CObject(ObjectType type, const std::string& name);

    /*!
     *  @brief the destructor of CObject.
     * 
     *  @details The function will be call when the json object is deleted, 
     *  and the memery will be free/delete.
     */
    ~CObject();

    /*!
     *  @brief the copy constructor of CObject.
     * 
     *  @details You can use this constructor to clone a new object from an exist object.
     *  All attributions are the same as the old one's
     * 
     *  @param other this object you want to copy from
     * 
     *  @note Before you add it to the list where the old object stays, you should change the name
     */
    CObject(const CObject& other);

    /*!
     *  @brief the overwrite operator of asign operator.
     * 
     *  @details You can use = to asign to each other
     *  as you want to 
     * 
     *  @param other this object you want to copy from
     * 
     *  @return the refrence of this object
     * 
     *  @note After you asign one to anothor, you should change the name
     */
    CObject& operator=(const CObject& other);

    /*!
     *  @brief the copy function.
     * 
     *  @details You can copy from other object by using this function 
     *  instead of using = or copy construct
     *  
     *  @param other this object you want to copy from
     * 
     *  @note After you asign one to anothor, you should change the name
     */
    void copy(const CObject& other);

    /*!
     *  @brief get the type of this object.
     * 
     *  @details You can get the ObjectType of this object
     *  as you want to
     *  
     *  @return the type of this object
     */
    ObjectType getType() const;

    /*!
     *  @brief get the name of this object.
     * 
     *  @details You can get the name of this object as you want to.
     *  If this object have no name, it will return empty string, for example:
     *  {} 
     *  
     *  @return the name of this object
     */
    std::string getName()const;

    /*!
     *  @brief get this object from its children by path
     * 
     *   @details the path sepeciate by names, it contains slash between two names,
     *  you can also replace the slash by other character.
     * 
     *  @param path the string path just like linux file system path
     *  @param sep the seperator of path, the default is "/" , you can pass a different character
     * 
     *  @return the pointer of this object speciated by path, 
     *   - the pointer of this object you can find
     *   - nullptr if can not found
     * 
     *  @note you must check whether the return value is nullptr or not before you use the result
     */
    const CObject* getObjectByPath(const char* path, const char* sep = PATH_SEP) const;

    /*!
     *  @brief get this object from its children by path
     * 
     *   @details the path sepeciate by names, it contains slash between two names,
     *  you can also replace the slash by other character.
     * 
     *  @param path the string path just like linux file system path
     *  @param sep the seperator of path, the default is "/" , you can pass a different character
     * 
     *  @return the pointer of this object speciated by path, 
     *   - the pointer of this object you can find
     *   - nullptr if can not found
     * 
     *  @note you must check whether the return value is nullptr or not before you use the result
     */
    const CObject* getObjectByPath(const std::string& path, const std::string& sep = PATH_SEP) const;

    /*!
     *  @brief get all children
     *  @details the children will return by using std::list
     * 
     *  @return the list of objects
     *   - empty list if there is no child
     *   - the list conatained all children
     * 
     *  @note if you change any object in this returned list, it will effect the child of this object
     */
    std::list<CObject*> getObjects()const;

    /*!
     *  @brief get the first object from children
     *  @details in the list, just like list::at(0)
     * 
     * @return the pointer of 1st object
     *   - the pointer of 1st object if there are children
     *   - nullptr if there no child
     */
    const CObject* getFirstObject()const;

    /*!
     *  @brief get the No. index object form children
     *  @details  in the list, just like list::at(index)
     *  
     *  @param index  the index position of this object you can in the list
     * 
     *  @return get this object from specical position
     *   - the pointer of this object you want to find  if there are children
     *   - nullptr if there no child
     */
    const CObject* getObjectByIndex(int index)const;

    /*!
     *  @brief get this object form children
     *  @details  whoes name is equite to name 
     *  
     *  @param name  the name of this object you want find in the list
     * 
     *  @return get this object from specical name
     *   - the pointer of this object you can if there are children
     *   - nullptr if there no child
     */
    const CObject* getObjectByName(const char* name) const;

    /*!
     *  @brief get this object form children
     *  @details  whoes name is equite to name 
     *  
     *  @param name  the name of this object you want find in the list
     * 
     *  @return get this object from specical name
     *   - the pointer of this object you can if there are children
     *   - nullptr if there no child
     */
    const CObject* getObjectByName(const std::string& name) const;

    /*!
     *  @brief get this object from its children by path
     * 
     *   @details the path sepeciate by names, it contains slash between two names,
     *  you can also replace the slash by other character.
     * 
     *  @param path the string path just like linux file system path
     *  @param sep the seperator of path, the default is "/" , you can pass a different character
     * 
     *  @return the pointer of this object speciated by path, 
     *   - the pointer of this object you can find
     *   - nullptr if can not found
     * 
     *  @note you must check whether the return value is nullptr or not before you use the result
     */
    CObject* getObjectByPath(const char* path, const char* sep = PATH_SEP);

    /*!
     *  @brief get this object from its children by path
     * 
     *   @details the path sepeciate by names, it contains slash between two names,
     *  you can also replace the slash by other character.
     * 
     *  @param path the string path just like linux file system path
     *  @param sep the seperator of path, the default is "/" , you can pass a different character
     * 
     *  @return the pointer of this object speciated by path, 
     *   - the pointer of this object you can find
     *   - nullptr if can not found
     * 
     *  @note you must check whether the return value is nullptr or not before you use the result
     */
    CObject* getObjectByPath(const std::string& path, const std::string& sep = PATH_SEP);

    /*!
     *  @brief get the first object from children
     *  @details in the list, just like list::at(0)
     * 
     * @return the pointer of 1st object
     *   - the pointer of 1st object if there are children
     *   - nullptr if there no child
     */
    CObject* getFirstObject();

    /*!
     *  @brief get the No. index object form children
     *  @details  in the list, just like list::at(index)
     *  
     *  @param index  the index position of this object you can in the list
     * 
     *  @return get this object from specical position
     *   - the pointer of this object you want to find  if there are children
     *   - nullptr if there no child
     */
    CObject* getObjectByIndex(int index);

    /*!
     *  @brief get this object form children
     *  @details  whoes name is equite to name 
     *  
     *  @param name  the name of this object you want find in the list
     * 
     *  @return get this object from specical name
     *   - the pointer of this object you can if there are children
     *   - nullptr if there no child
     */
    CObject* getObjectByName(const char* name);

    /*!
     *  @brief get this object form children
     *  @details  whoes name is equite to name 
     *  
     *  @param name  the name of this object you want find in the list
     * 
     *  @return get this object from specical name
     *   - the pointer of this object you can if there are children
     *   - nullptr if there no child
     */
    CObject* getObjectByName(const std::string& name);

    /*!
     *  @brief overwite operator [], get the No. index object form children
     *  @details  in the list, just like list::at(index)
     *  
     *  @param index  the index position of this object you can in the list
     * 
     *  @return get this object from specical position
     *   - the pointer of this object you want to find  if there are children
     *   - nullptr if there no child
     */
    const CObject& operator[](int index)const;

    /*!
     *  @brief overwite operator [], get this object form children
     *  @details  whoes name is equite to name 
     *  
     *  @param name  the name of this object you want find in the list
     * 
     *  @return get this object from specical name
     *   - the pointer of this object you can if there are children
     *   - nullptr if there no child
     */
    const CObject& operator[](const char* name)const;

    /*!
     *  @brief overwite operator [], get this object form children
     *  @details  whoes name is equite to name 
     *  
     *  @param name  the name of this object you want find in the list
     * 
     *  @return get this object from specical name
     *   - the pointer of this object you can if there are children
     *   - nullptr if there no child
     */
    const CObject& operator[](const std::string& name)const;

    /*!
     *  @brief get the index of this object
     *  @details  speciated by param obj 
     *  
     *  @param obj  the name of this object you want find in the list
     * 
     *  @return get this object from specical name
     *   - the pointer of this object you can if there are children
     *   - nullptr if there no child
     */
    int getObjectIndex(CObject* obj)const;

    /*!
     *  @brief overwite operator [], get this object by index
     *  @details  speciated by param index 
     *  
     *  @param index  No. index object you want find in the list
     * 
     *  @return get this object from specical index
     *   - the pointer of this object you can if there are children
     *   - nullptr if there no child or the index is not right
     */
    CObject& operator[](int index);

    /*!
     *  @brief overwite operator [], get this object form children
     *  @details  whoes name is equite to name 
     *  
     *  @param name  the name of this object you want find in the list
     * 
     *  @return get this object from specical name
     *   - the pointer of this object you can if there are children
     *   - nullptr if there no child
     */
    CObject& operator[](const char* name);

    /*!
     *  @brief overwite operator [], get this object form children
     *  @details  whoes name is equite to name 
     *  
     *  @param name  the name of this object you want find in the list
     * 
     *  @return get this object from specical name
     *   - the pointer of this object you can if there are children
     *   - nullptr if there no child
     */
    CObject& operator[](const std::string& name);

     /*!
     *  @brief get the index of this object
     *  @details  speciated by param obj 
     *  
     *  @param obj  the name of this object you want find in the list
     * 
     *  @return get this object from specical name
     *   - the pointer of this object you can if there are children
     *   - nullptr if there no child
     */
   int getObjectIndex(CObject* obj);

    /*!
     *  @brief move this object to the special position
     *  @details  speciated by param index , if the obj is nullptr/NULL, it will also return -1.
     *  
     *  @param obj  this object you want to move
     *  @param index  the position you want to move to, if you want to move to the end, please asign -1
     * 
     *  @return the new position
     *   - equite or greate than 0 
     *   - -1 if there are some errors
     */
    int moveObject(CObject* obj, int index = -1);

    /*!
     *  @brief get the count/size of the children
     *  @details  s
     *  
     *  @return the count/size of the children
     *   - 0 if it is empty 
     *   - greater than 0 if it isn't empty
     */
    int countObject()const;

    /*!
     *  @brief Remove the special object
     *  @details whether deleted or not depend on the param bAlsoDelete
     *  
     *  @param obj this object you want to remove
     *  @param bAlsoDelete if true, this object will be deleted
     *   otherwise will not (default is true)
     *  @return return the result of remove operation
     *   - true if success 
     *   - false if fail
     * 
     *  @note If bAlsoDelete is true, you should not delete this object manually
     *    otherwise the program will crash
     */
    bool removeObject(CObject* obj, bool bAlsoDelete = true);

    /*!
     *  @brief Remove all children
     *  @details whether deleted or not depend on the param bAlsoDelete
     *  
     *  @param bAlsoDelete if true, this object will be deleted
     *   otherwise will not (default is true)
     *  @return return the result of remove operation
     *   - true if success 
     *   - false if fail
     * 
     *  @note If bAlsoDelete is true, you should not delete this object manually
     *    otherwise the program will crash
     */
    void removeAllObjects(bool bAlsoDelete = true);

    /*!
     *  @brief converte the value of this object to bool type value
     *  @details but doesn't  modify the type of this object,
     *   it is always successful
     *  
     *  @param ok if ok is not zero, the translated result will be stored in this variable
     *  @return return the boolean value
     *   - true if the value is true and the type is kBool 
     *   - true if the value is not zero and the type is kUInt64/kInt64/kDouble
     *   - true if the value string is not empty and the type is kString 
     *   - true if the value of children is notempty and the type is kArray/kObject 
     *   - false otherwise 
     */
    bool toBool(bool *ok = 0)const;

    /*!
     *  @brief converte the value of this object to int32_t type value
     *  @details but doesn't  modify the type of this object.
     *   If there are errors, *ok will be set false. For example,
     *   the string value which is empty can not be translated to number, *ok will be
     *   set false.
     *  
     *  @param ok if ok is not zero, the translated result will be stored in this variable
     *  @return return the int32_t value
     * 
     *  @note If the *ok is false, return value is meanless.
     */
    int32_t toInt32(bool *ok = 0)const;

    /*!
     *  @brief converte the value of this object to uint32_t type value
     *  @details but doesn't  modify the type of this object.
     *   If there are errors, *ok will be set false. For example,
     *   the string value which is empty can not be translated to number, *ok will be
     *   set false.
     *  
     *  @param ok if ok is not zero, the translated result will be stored in this variable
     *  @return return the uint32_t value
     * 
     *  @note If the *ok is false, return value is meanless.
     */
    uint32_t toUInt32(bool *ok = 0)const;

    /*!
     *  @brief converte the value of this object to uint64_t type value
     *  @details but doesn't  modify the type of this object.
     *   If there are errors, *ok will be set false. For example,
     *   the string value which is empty can not be translated to number, *ok will be
     *   set false.
     *  
     *  @param ok if ok is not zero, the translated result will be stored in this variable
     *  @return return the uint64_t value
     * 
     *  @note If the *ok is false, return value is meanless.
     */
    uint64_t toUInt64(bool *ok = 0)const;

    /*!
     *  @brief converte the value of this object to int64_t type value
     *  @details but doesn't  modify the type of this object.
     *   If there are errors, *ok will be set false. For example,
     *   the string value which is empty can not be translated to number, *ok will be
     *   set false.
     *  
     *  @param ok if ok is not zero, the translated result will be stored in this variable
     *  @return return the int64_t value
     * 
     *  @note If the *ok is false, return value is meanless.
     */
    int64_t toInt64(bool *ok = 0)const;

    /*!
     *  @brief converte the value of this object to double type value
     *  @details but doesn't  modify the type of this object.
     *   If there are errors, *ok will be set false. For example,
     *   the string value which is empty can not be translated to number, *ok will be
     *   set false.
     *  
     *  @param ok if ok is not zero, the translated result will be stored in this variable
     *  @return return the double value
     * 
     *  @note If the *ok is false, return value is meanless.
     */
    double toDouble(bool *ok = 0)const;

    /*!
     *  @brief converte the value of this object to string value
     *  @details but doesn't  modify the type of this object.
     *   it is always successful
     *  
     *  @param ok if ok is not zero, the translated result will be stored in this variable
     *  @return return the double value
     * 
     *  @note If the *ok is false, return value is meanless.
     */
    std::string toString(bool *ok = 0)const;
 
    /*!
     *  @brief converte the value of this object to array value(COjectArray)
     *  @details but doesn't  modify the type of this object.
     *   it is successful if the type is kArray/kObject
     *  
     *  @param ok if ok is not zero, the translated result will be stored in this variable
     *  @return return the double value
     * 
     *  @note If the *ok is false, return value is meanless.
     */
    const CObjectArray& toArray(bool *ok = 0)const;

    /*!
     *  @brief converte the value of this object to array value(COjectArray)
     *  @details but doesn't  modify the type of this object.
     *   it is successful if the type is kArray/kObject
     *  
     *  @param ok if ok is not zero, the translated result will be stored in this variable
     *  @return return the double value
     * 
     *  @note If the *ok is false, return value is meanless.
     */
    CObjectArray toArray(bool *ok = 0);

    /*!
     *  @brief set null value
     *  @details if the type is no kNull, it will be set kNull. 
     */
    void setNull();

    /*!
     *  @brief set bool value
     *  @details if the type is no kBool, it will be set kBool. 
     * 
     *  @param value the new value will be set to this object
     */
    void setValue(bool value);

    /*!
     *  @brief set uint32_t value
     *  @details if the type is no kUInt64, it will be set kUInt64. 
     * 
     *  @param value the new value will be set to this object
     */
    void setValue(uint32_t value);

    /*!
     *  @brief set int32_t value
     *  @details if the type is no kInt64, it will be set kInt64. 
     * 
     *  @param value the new value will be set to this object
     */
    void setValue(int32_t value);

    /*!
     *  @brief set uint64_t value
     *  @details if the type is no kUInt64, it will be set kUInt64. 
     * 
     *  @param value the new value will be set to this object
     */
    void setValue(uint64_t value);
    
    /*!
     *  @brief set int64_t value
     *  @details if the type is no kInt64, it will be set kInt64. 
     * 
     *  @param value the new value will be set to this object
     */
    void setValue(int64_t value);

    /*!
     *  @brief set double value
     *  @details if the type is no kInt64, it will be set kInt64. 
     * 
     *  @param value the new value will be set to this object
     */
    void setValue(double value);

    /*!
     *  @brief set c string value
     *  @details if the type is no kString, it will be set kString. 
     * 
     *  @param value the new value will be set to this object
     */
    void setValue(const char* value);

    /*!
     *  @brief set string value
     *  @details if the type is no kString, it will be set kString. 
     * 
     *  @param value the new value will be set to this object
     */
    void setValue(const std::string& value);

    /*!
     *  @brief set c string value
     *  @details if the type is no kString, it will be set kString. 
     * 
     *  @param value the new value will be set to this object
     *  @param type the new type will be set to this object
     * 
     *  @note only kArray/kObject is supported in param type
     */
    void setValue(const CObjectArray& value, ObjectType type);

    /*!
     *  @brief set bool value
     *  @details if the type is no kBool, it will be set kBool. 
     * 
     *  @param value the new value will be set to this object
     */
    CObject& operator=(bool value);

    /*!
     *  @brief set uint32_t value
     *  @details if the type is no kUInt64, it will be set kUInt64. 
     * 
     *  @param value the new value will be set to this object
     */
    CObject& operator=(uint32_t value);

    /*!
     *  @brief set int32_t value
     *  @details if the type is no kInt64, it will be set kInt64. 
     * 
     *  @param value the new value will be set to this object
     */
    CObject& operator=(int32_t value);

    /*!
     *  @brief set uint64_t value
     *  @details if the type is no kUInt64, it will be set kUInt64. 
     * 
     *  @param value the new value will be set to this object
     */
    CObject& operator=(uint64_t value);

    /*!
     *  @brief set int64_t value
     *  @details if the type is no kInt64, it will be set kInt64. 
     * 
     *  @param value the new value will be set to this object
     */
    CObject& operator=(int64_t value);
    
    /*!
     *  @brief set double value
     *  @details if the type is no kInt64, it will be set kInt64. 
     * 
     *  @param value the new value will be set to this object
     */
    CObject& operator=(double value);

    /*!
     *  @brief set c string value
     *  @details if the type is no kString, it will be set kString. 
     * 
     *  @param value the new value will be set to this object
     */
    CObject& operator=(const char* value);

    /*!
     *  @brief set string value
     *  @details if the type is no kString, it will be set kString. 
     * 
     *  @param value the new value will be set to this object
     */
    CObject& operator=(const std::string& value);

    /*!
     *  @brief Add new object to its children list
     *  @details and then return the value indicating whether success or not. 
     * 
     *  @param obj the new object pointer you want to add
     * 
     *  @return return the value
     *   - return false if the current type isn't kObject/kArray or the obj is nullptr
     *   - return true otherwise
     * 
     *  @note After adding, the lifetime of this object will be managed by this class ,
     *  user can not delete the object pointed by param obj
     */
    bool addChild(CObject* obj);

    /*!
     *  @brief Serialize this object to string
     *  @details and then return the value indicating whether success or not. 
     * 
     *  @return return the serial string from this object
     * 
     */
    std::string serialString()const;

protected:
    friend class CObjectDocument;           /*! @brief @see CObjectDocument */
    friend class CObjectDocumentPrivate;    /*! @brief @see CObjectDocumentPrivate */

    /*!
     *  @brief write this object to handle
     *  @details this will be use in class inner space. 
     * 
     *  @return return the result
     *   - true if success
     *   -- false if fail
     * 
     *  @note This handle must be the pointer of below:     * 
     *  @code{.cpp}
     *  rapidjson::PrettyWriter<rapidjson::FileWriteStream, 
     *      rapidjson::UTF8<>, 
     *      rapidjson::UTF8<>, 
     *      rapidjson::CrtAllocator, 
     *      rapidjson::kWriteValidateEncodingFlag>
     *  @endcode
     */
    bool write(void *handle)const;

    /*!
     *  @brief Serialize this object to handle
     *  @details this will be use in class inner space. 
     * 
     *  @return return the result
     *   - true if success
     *   -- false if fail
     * 
     *  @note This handle must be the pointer of below:
     *  @code{.cpp}
     *  rapidjson::PrettyWriter<rapidjson::StringBuffer, 
            rapidjson::UTF8<>, rapidjson::UTF8<>, rapidjson::CrtAllocator, 
            rapidjson::kWriteValidateEncodingFlag>
     *  @endcode
     */
    bool writeStringHandle(void *handle)const;

    /*!
     *  @brief Clean the object resources
     *  @details Clean the name and free the name memery
     *   Set type to kInvalid
     *   clean and free the children
     */
    void cleanValue();

private:
    /*! This is an union inner definition of the ObjectValue. */
    typedef union
    {
        bool            m_flag;     /*!< boolean value */
        uint64_t        m_u64;      /*!< uint64_t value */
        int64_t         m_i64;      /*!< int64_t value */
        double          m_double;   /*!< double value */
        std::string*    m_string;   /*!< string value */
        CObjectArray*   m_children; /*!< children value(array) */
    }ObjectValue;

    std::string*        m_name;     /*!< name string pointer */
    ObjectType          m_type;     /*!< type */
    ObjectValue         m_value;    /*!< children value(array) */      
};

} // jsconfig

#endif // JSCONFIG_OBJECT_H__
