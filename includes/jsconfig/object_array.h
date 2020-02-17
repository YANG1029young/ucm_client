/***************************************************************************//**
 * @copyright Copyright (c) by Hinge-Tech R&D Center.
 * @file  object_array.h
 * @brief Head file for declaring class CObjectArray.
 * @author Rimon Chen 
 * @version 01.00.00
 * @date  2019-06-27
 * @par Description declare class CObjectArray
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
#ifndef JSCONFIG_OBJECT_ARRAY_H__
#define JSCONFIG_OBJECT_ARRAY_H__

#include <string>
#include <list>
#include "jsconfig/common.h"

namespace jsconfig
{
class CObject;

/*!
 *  @brief Json object araay class .
 *  
 *  @details This class can be used to represend a list of object
 *   in json file,
 *  every object contain the key and value. 
 *  the value includes the string, the number etc.
 */
class JSCONFIG_API CObjectArray
{
public:
    /*!
     *  @brief The default constructor of CObjectArray.
     * 
     *  @details If you  create an instance of CObjectArray by using this
     *  default constructor, you will get a variant object 
     *  whiches list is empty
     */
    CObjectArray();

     /*!
     *  @brief The destructor of CObjectArray.
     * 
     *  @details The function will be call when the json object array is deleted, 
     *  and the members will be free/delete.
     */
   ~CObjectArray();

    /*!
     *  @brief The copy constructor of CObjectArray.
     * 
     *  @details You can use this constructor to clone a new object from an exist object.
     *  The list are the same as the old one's
     * 
     *  @param other this object you want to copy from
     * 
     *  @note Before you add it to the list where the old object stays, 
     *   you should change the name for each every element in the list
     */
    CObjectArray(const CObjectArray& other);

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
     *  @note After you asign one to anothor, 
     *   you should change the name for each every element in the list
     */
    CObjectArray& operator=(const CObjectArray& other);

    /*!
     *  @brief the copy function.
     * 
     *  @details You can copy from other object by using this function 
     *  instead of using = or copy construct
     *  
     *  @param other this object you want to copy from
     * 
     *  @note After you asign one to anothor, 
     *  you should change the name for each every element in the list
     */
    void copy(const CObjectArray& other);

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
    const CObject* getObject(int index)const;

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
    const CObject* getObject(const char* name)const;
    
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
    const CObject* getObject(const std::string& name)const;

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
    CObject* getObject(int index);
    
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
    CObject* getObject(const char* name);
    
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
    CObject* getObject(const std::string& name);

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
     *  @brief overwite operator [], get the No. index object form children
     *  @details  in the list, just like list::at(index)
     *  
     *  @param index  the index position of this object you can in the list
     * 
     *  @return get this object from specical position
     *   - the pointer of this object you want to find  if there are children
     *   - nullptr if there no child
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
    bool addObject(CObject* obj);

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


private:
    std::list<CObject*> m_datas; /*!< list data in array */
};

} // jsconfig

#endif // JSCONFIG_OBJECT_ARRAY_H__
