/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_BINDING_DESERIALIZER_H_
#define ARA_COM_INTERNAL_BINDING_DESERIALIZER_H_

#include <cstdint>
#include <string>
#include <vector>
#include <string.h>
#include <map>
#include <cmath>

#include <ara/com/internal/common.h>
#include <ara/com/internal/binding/common.h>

#include <ara/core/optional.h>
#include <ara/core/variant.h>

namespace ara
{
namespace com
{
namespace internal
{
namespace binding
{

class Deserializer
{
public:
    Deserializer(const uint8_t *data, uint32_t size)
        : m_data(data), m_size(size)
    {
    }
    
    virtual ~Deserializer()
    {
    }
    
    virtual bool Deserialize(bool& value) = 0;
    virtual bool Deserialize(uint8_t& value) = 0;
    virtual bool Deserialize(uint16_t& value) = 0;
    virtual bool Deserialize(uint32_t& value) = 0;
    virtual bool Deserialize(uint64_t& value) = 0;
    virtual bool Deserialize(int8_t& value) = 0;
    virtual bool Deserialize(int16_t& value) = 0;
    virtual bool Deserialize(int32_t& value) = 0;
    virtual bool Deserialize(int64_t& value) = 0;
    virtual bool Deserialize(float& value) = 0;
    virtual bool Deserialize(double& value) = 0;
    virtual bool Deserialize(std::string& value) = 0;
    
    virtual int Deserialize(bool& value, const uint8_t *data, uint32_t size) = 0;
    virtual int Deserialize(uint8_t& value, const uint8_t *data, uint32_t size) = 0;
    virtual int Deserialize(uint16_t& value, const uint8_t *data, uint32_t size) = 0;
    virtual int Deserialize(uint32_t& value, const uint8_t *data, uint32_t size) = 0;
    virtual int Deserialize(uint64_t& value, const uint8_t *data, uint32_t size) = 0;
    virtual int Deserialize(int8_t& value, const uint8_t *data, uint32_t size) = 0;
    virtual int Deserialize(int16_t& value, const uint8_t *data, uint32_t size) = 0;
    virtual int Deserialize(int32_t& value, const uint8_t *data, uint32_t size) = 0;
    virtual int Deserialize(int64_t& value, const uint8_t *data, uint32_t size) = 0;
    virtual int Deserialize(float& value, const uint8_t *data, uint32_t size) = 0;
    virtual int Deserialize(double& value, const uint8_t *data, uint32_t size) = 0;
    virtual int Deserialize(std::string& value, const uint8_t *data, uint32_t size) = 0;
    
    virtual bool Deserialize(uint16_t dataId, ara::core::Optional<bool>& value) = 0;
    virtual bool Deserialize(uint16_t dataId, ara::core::Optional<uint8_t>& value) = 0;
    virtual bool Deserialize(uint16_t dataId, ara::core::Optional<uint16_t>& value) = 0;
    virtual bool Deserialize(uint16_t dataId, ara::core::Optional<uint32_t>& value) = 0;
    virtual bool Deserialize(uint16_t dataId, ara::core::Optional<uint64_t>& value) = 0;
    virtual bool Deserialize(uint16_t dataId, ara::core::Optional<int8_t>& value) = 0;
    virtual bool Deserialize(uint16_t dataId, ara::core::Optional<int16_t>& value) = 0;
    virtual bool Deserialize(uint16_t dataId, ara::core::Optional<int32_t>& value) = 0;
    virtual bool Deserialize(uint16_t dataId, ara::core::Optional<int64_t>& value) = 0;
    virtual bool Deserialize(uint16_t dataId, ara::core::Optional<float>& value) = 0;
    virtual bool Deserialize(uint16_t dataId, ara::core::Optional<double>& value) = 0;
    virtual bool Deserialize(uint16_t dataId, ara::core::Optional<std::string>& value) = 0;
    
protected:    
    virtual bool DeserializeStructSize(uint32_t& size) = 0;
    virtual bool DeserializeVectorSize(uint32_t& size) = 0;
    virtual bool DeserializeArraySize(uint32_t& size) = 0;
    virtual bool DeserializeMapSize(uint32_t& size) = 0;
    virtual bool DeserializeTagStructSize(const uint16_t& tag, uint32_t& size) = 0;
    virtual bool DeserializeTagVectorSize(const uint16_t& tag, uint32_t& size) = 0;
    virtual bool DeserializeTagArraySize(const uint16_t& tag, uint32_t& size) = 0;
    virtual bool DeserializeTagMapSize(const uint16_t& tag, uint32_t& size) = 0;
    virtual bool CheckTag(const uint16_t& tag, const uint16_t& tagData) = 0;

public:    
    template <typename T>
    bool Deserialize(T& value, typename std::enable_if<std::is_enum<T>::value>::type* = 0)
    {        
        if (sizeof(T) == 1)
        {
            uint8_t enum_val = 0;
            if (Deserialize(enum_val))
            {
                value = (T)enum_val;
            }
            else
            {
                return false;
            }
        }
        else if (sizeof(T) == 2)
        {
            uint16_t enum_val = 0;
            if (Deserialize(enum_val))
            {
                value = (T)enum_val;
            }
            else
            {
                return false;
            }
        }
        else if (sizeof(T) == 4)
        {
            uint32_t enum_val = 0;
            if (Deserialize(enum_val))
            {
                value = (T)enum_val;
            }
            else
            {
                return false;
            }
        }
        else if (sizeof(T) == 8)
        {
            uint64_t enum_val = 0;
            if (Deserialize(enum_val))
            {
                value = (T)enum_val;
            }
            else
            {
                return false;
            }
        }
        
        return true;
    }
    
    template <typename T>
    bool Deserialize(T& value,
        typename std::enable_if<!is_enumerable<T>::value && !std::is_enum<T>::value && std::is_trivially_copyable<T>::value>::type* = 0)
    {
        if (m_size < sizeof(T))
        {
            return false;
        }
        
        uint8_t* data = reinterpret_cast<uint8_t*>(&value);
        memcpy(data, m_data, sizeof(T));
        
        m_size -= sizeof(T);
        m_data += sizeof(T);
        
        return true;
    }
    
    template <typename T>
    bool Deserialize(T& value,
        typename std::enable_if<is_enumerable<T>::value>::type* = 0)
    {
        uint32_t size;
        if (!DeserializeStructSize(size))
        {
            return false;
        }
        
        return value.Deserialize(this);
    }
    
    template <typename T>
    bool Deserialize(std::vector<T>& value)
    {
        value.clear();
        
        uint32_t size = 0;
        if (!DeserializeVectorSize(size))
        {
            return false;
        }
        
        uint32_t beginSize = m_size;
        while (size > (beginSize - m_size))
        {
            T v;
            if (!Deserialize(v))
            {
                return false;
            }
            
            value.push_back(v);
        }
        
        return true;
    }
    
    template <typename T, std::size_t SIZE>
    bool Deserialize(std::array<T,SIZE>& value)
    {        
        uint32_t size = SIZE;
        
        std::size_t i = 0;
        
        while (size > i)    
        {   
            T v;
            if (!Deserialize(v))
            {
                return false;
            }
            
            value[i] = v;
            i++;
        }
        
        return true;
    }
    
    template <typename KEY, typename VALUE>
    bool Deserialize(std::map<KEY, VALUE>& value)
    {
        value.clear();
        
        uint32_t size = 0;
        if (!DeserializeMapSize(size))
        {
            return false;
        }
        
        uint32_t beginSize = m_size;
        while (size > (beginSize - m_size))
        {
            KEY k;
            if (!Deserialize(k))
            {
                return false;
            }
            
            VALUE v;
            if (!Deserialize(v))
            {
                return false;
            }
            
            value[k] = v;
        }
        
        return true;
    }
    
    
    
    
    template <typename T>
    bool Deserialize(uint16_t dataId, ara::core::Optional<T>& value, typename std::enable_if<std::is_enum<T>::value>::type* = 0)
    {
        if (m_size < 2)
        {
            return true;
        }
        
        uint16_t tag = 0;
        uint8_t wrieType = std::log(sizeof(T)) / std::log(2);
        tag = wrieType;
        tag = tag << 12;
        tag += dataId & 0x0FFF;
    
        const uint16_t* tag_ptr = reinterpret_cast<const uint16_t*>(m_data);
        if (CheckTag(tag, *tag_ptr))
        {
            T v;
            
            if (!Deserialize(v))
            {
                return false;
            }
        
            value = v;
        }
    
        return true;
    }
    
    template <typename T>
    bool Deserialize(uint16_t dataId, ara::core::Optional<T>& value,
        typename std::enable_if<!is_enumerable<T>::value && !std::is_enum<T>::value && std::is_trivially_copyable<T>::value>::type* = 0)
    {
        if (m_size < 2)
        {
            return true;
        }
        
        uint16_t tag = 0;
        uint8_t wrieType = std::log(sizeof(T)) / std::log(2);
        tag = wrieType;
        tag = tag << 12;
        tag += dataId & 0x0FFF;
    
        const uint16_t* tag_ptr = reinterpret_cast<const uint16_t*>(m_data);
        if (CheckTag(tag, *tag_ptr))
        {            
            T v;
            
            if (!Deserialize(v))
            {
                return false;
            }
        
            value = v;
        }
    
        return true;
    }
    
    template <typename T>
    bool Deserialize(uint16_t dataId, ara::core::Optional<T>& value,
        typename std::enable_if<is_enumerable<T>::value>::type* = 0)
    {
        if (m_size < 2)
        {
            return true;
        }
        
        uint16_t tag = 0;
        uint8_t wrieType = 7;
        tag = wrieType;
        tag = tag << 12;
        tag += dataId & 0x0FFF;

        uint32_t size = 0;
        if (DeserializeTagStructSize(tag, size))
        {
            T v;
        
            if (!v.Deserialize(this))
            {
                return false;
            }
        
            value = v;
        }
        
        return true;
    }
    
    template <typename T>
    bool Deserialize(uint16_t dataId, ara::core::Optional<std::vector<T>>& value)
    {
        if (m_size < 2)
        {
            return true;
        }
        
        uint16_t tag = 0;
        uint8_t wrieType = 7;
        tag = wrieType;
        tag = tag << 12;
        tag += dataId & 0x0FFF;
        
        uint32_t size = 0;
        if (DeserializeTagVectorSize(tag, size))
        {
            uint32_t beginSize = m_size;
            std::vector<T> value_d;
        
            while (size > (beginSize - m_size))
            {
                T v;
                if (!Deserialize(v))
                {
                    return false;
                }
            
                value_d.push_back(v);
            }
            
            value = value_d;
        }
        
        return true;
    }
    
    template <typename T, std::size_t SIZE>
    bool Deserialize(uint16_t dataId, ara::core::Optional<std::array<T,SIZE>>& value)
    {
        if (m_size < 2)
        {
            return true;
        }
                
        uint16_t tag = 0;
        uint8_t wrieType = 7;
        tag = wrieType;
        tag = tag << 12;
        tag += dataId & 0x0FFF;

        uint32_t size = 0;
        if (DeserializeTagArraySize(tag, size))
        {
            uint32_t beginSize = m_size;
            std::size_t i = 0;
            std::array<T,SIZE> value_d;
        
            while (size > (beginSize - m_size))
            {
                if (i >= SIZE)
                {
                    logger().LogError() << CODE_POS(__FILE__, __FUNCTION__, __LINE__) << "i >= SIZE";
                    return false;
                }
            
                T v;
                if (!Deserialize(v))
                {
                    return false;
                }
            
                value_d[i++] = v;
            }
            
            value = value_d;
        }
        
        return true;
    }
    
    template <typename KEY, typename VALUE>
    bool Deserialize(uint16_t dataId, ara::core::Optional<std::map<KEY, VALUE>>& value)
    {
        if (m_size < 2)
        {
            return true;
        }
        
        uint16_t tag = 0;
        uint8_t wrieType = 7;
        tag = wrieType;
        tag = tag << 12;
        tag += dataId & 0x0FFF;

        uint32_t size = 0;
        if (DeserializeTagMapSize(tag, size))
        {
            uint32_t beginSize = m_size;
            std::map<KEY, VALUE> value_d;
        
            while (size > (beginSize - m_size))
            {
                KEY k;
                if (!Deserialize(k))
                {
                    return false;
                }
            
                VALUE v;
                if (!Deserialize(v))
                {
                    return false;
                }
            
                value_d[k] = v;
            }
            
            value = value_d;
        }
        
        return true;
    }
    
    template <typename T>
    int Deserialize(T& value, const uint8_t *data, uint32_t size, typename std::enable_if<std::is_enum<T>::value>::type* = 0)
    {        
        m_data = data;
        m_size = size;
        
        if (!Deserialize(value))
        {
            return 0;
        }
        
        return size - m_size;
    }
    
    template <typename T>
    int Deserialize(T& value, const uint8_t *data, uint32_t size,
        typename std::enable_if<!is_enumerable<T>::value && !std::is_enum<T>::value && std::is_trivially_copyable<T>::value>::type* = 0)
    {        
        m_data = data;
        m_size = size;
        
        if (!Deserialize(value))
        {
            return 0;
        }
        
        return size - m_size;
    }
    
    template <typename T>
    int Deserialize(T& value, const uint8_t *data, uint32_t size,
        typename std::enable_if<is_enumerable<T>::value>::type* = 0)
    {

        m_data = data;
        m_size = size;
        
        if (!Deserialize(value))
        {
            return 0;
        }
        
        return size - m_size;
    }
    
    template <typename T>
    int Deserialize(std::vector<T>& value, const uint8_t *data, uint32_t size)
    {
        m_data = data;
        m_size = size;
        
        if (!Deserialize(value))
        {
            return 0;
        }
        
        return size - m_size;
    }
    
    template <typename T, std::size_t SIZE>
    int Deserialize(std::array<T,SIZE>& value, const uint8_t *data, uint32_t size)
    {
        m_data = data;
        m_size = size;
        
        if (!Deserialize(value))
        {
            return 0;
        }
        
        return size - m_size;
    }
    
    template <typename KEY, typename VALUE>
    int Deserialize(std::map<KEY, VALUE>& value, const uint8_t *data, uint32_t size)
    {
        m_data = data;
        m_size = size;
        
        if (!Deserialize(value))
        {
            return 0;
        }
        
        return size - m_size;
    }
    
protected:
    const uint8_t* m_data;
    uint32_t m_size;
//    std::shared_ptr<ApTransformationProps> m_transformationProps;
};

} // binding
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_BINDING_DESERIALIZER_H_
