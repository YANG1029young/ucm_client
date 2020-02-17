/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_BINDING_SERIALIZER_H_
#define ARA_COM_INTERNAL_BINDING_SERIALIZER_H_

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <cmath>

#include <ara/com/internal/common.h>
#include <ara/com/internal/binding/common.h>

#include <ara/core/optional.h>

namespace ara
{
namespace com
{
namespace internal
{
namespace binding
{


class Serializer
{
public:
    Serializer()
        : m_container(std::make_shared<std::vector<uint8_t>>())
    {
    }
    
    virtual ~Serializer()
    {
    }
    
    std::shared_ptr<std::vector<uint8_t>> GetPayload()
    {
        return m_container;
    }
    
    virtual void Serialize(const bool& value) = 0;
    virtual void Serialize(const uint8_t& value) = 0;
    virtual void Serialize(const uint16_t& value) = 0;
    virtual void Serialize(const uint32_t& value) = 0;
    virtual void Serialize(const uint64_t& value) = 0;
    virtual void Serialize(const int8_t& value) = 0;
    virtual void Serialize(const int16_t& value) = 0;
    virtual void Serialize(const int32_t& value) = 0;
    virtual void Serialize(const int64_t& value) = 0;
    virtual void Serialize(const float& value) = 0;
    virtual void Serialize(const double& value) = 0;
    virtual void Serialize(const std::string& value) = 0;
    
    virtual void Serialize(uint16_t dataId, const ara::core::Optional<bool>& value) = 0;
    virtual void Serialize(uint16_t dataId, const ara::core::Optional<uint8_t>& value) = 0;
    virtual void Serialize(uint16_t dataId, const ara::core::Optional<uint16_t>& value) = 0;
    virtual void Serialize(uint16_t dataId, const ara::core::Optional<uint32_t>& value) = 0;
    virtual void Serialize(uint16_t dataId, const ara::core::Optional<uint64_t>& value) = 0;
    virtual void Serialize(uint16_t dataId, const ara::core::Optional<int8_t>& value) = 0;
    virtual void Serialize(uint16_t dataId, const ara::core::Optional<int16_t>& value) = 0;
    virtual void Serialize(uint16_t dataId, const ara::core::Optional<int32_t>& value) = 0;
    virtual void Serialize(uint16_t dataId, const ara::core::Optional<int64_t>& value) = 0;
    virtual void Serialize(uint16_t dataId, const ara::core::Optional<float>& value) = 0;
    virtual void Serialize(uint16_t dataId, const ara::core::Optional<double>& value) = 0;
    virtual void Serialize(uint16_t dataId, const ara::core::Optional<std::string>& value) = 0;

protected:    
    virtual void SerializeStructSize(const uint32_t& beginSize) = 0;
    virtual void SerializeVectorSize(const uint32_t& beginSize) = 0;
    virtual void SerializeArraySize(const uint32_t& beginSize) = 0;
    virtual void SerializeMapSize(const uint32_t& beginSize) = 0;
    virtual void SerializeStructTag(const uint16_t& dataId) = 0;
    virtual void SerializeVectorTag(const uint16_t& dataId) = 0;
    virtual void SerializeArrayTag(const uint16_t& dataId) = 0;
    virtual void SerializeMapTag(const uint16_t& dataId) = 0;
    virtual void SerializeTag(const uint16_t& tag) = 0;

public:    
    template <typename T>
    void Serialize(const T& value, typename std::enable_if<std::is_enum<T>::value>::type* = 0)
    {
        if (sizeof(T) == 1)
        {
            uint8_t enum_val = (uint8_t)value;
            Serialize(enum_val);
        }
        else if (sizeof(T) == 2)
        {
            uint16_t enum_val = (uint16_t)value;
            Serialize(enum_val);
        }
        else if (sizeof(T) == 4)
        {
            uint32_t enum_val = (uint32_t)value;
            Serialize(enum_val);
        }
        else if (sizeof(T) == 8)
        {
            uint64_t enum_val = (uint64_t)value;
            Serialize(enum_val);
        }
    }
    
    template <typename T>
    void Serialize(const T& value, typename std::enable_if<!is_enumerable<T>::value && !std::is_enum<T>::value && std::is_trivially_copyable<T>::value>::type* = 0)
    {
        const uint8_t* data = reinterpret_cast<const uint8_t*>(&value);
        m_container->insert(m_container->end(), data, data + sizeof(T));
    }
    
    template <typename T>
    void Serialize(const T& value, typename std::enable_if<is_enumerable<T>::value>::type* = 0)
    {
        uint32_t beginSize = m_container->size();
        value.Serialize(this);
        SerializeStructSize(beginSize);
    }
    
    template <typename T>
    void Serialize(const std::vector<T>& value)
    {
        uint32_t beginSize = m_container->size();

        for(T v : value)
        {
            Serialize(v);
        }
        
        SerializeVectorSize(beginSize);
    }
    
    template <typename T, std::size_t SIZE>
    void Serialize(const std::array<T,SIZE>& value)
    {
        //uint32_t beginSize = m_container->size();

        for(T v : value)
        {
            Serialize(v);
        }
        
        //SerializeArraySize(beginSize);
    }
    
    template <typename KEY, typename VALUE>
    void Serialize(const std::map<KEY,VALUE>& value)
    {
        uint32_t beginSize = m_container->size();

        for(auto v : value)
        {
            Serialize(v.first);
            Serialize(v.second);
        }
        
        SerializeMapSize(beginSize);
    }
    
    template <typename T>
    void Serialize(uint16_t dataId, const ara::core::Optional<T>& value, typename std::enable_if<std::is_enum<T>::value>::type* = 0)
    {        
        if (value.has_value())
        {
            uint16_t tag = 0;
            uint8_t wrieType = std::log(sizeof(T)) / std::log(2);
            tag = wrieType;
            tag = tag << 12;
            tag += dataId & 0x0FFF;
    
            SerializeTag(tag);
        
            Serialize(value.value());
        }
    }
    
    template <typename T>
    void Serialize(uint16_t dataId, const ara::core::Optional<T>& value,
        typename std::enable_if<!is_enumerable<T>::value && !std::is_enum<T>::value && std::is_trivially_copyable<T>::value>::type* = 0)
    {        
        if (value.has_value())
        {
            uint16_t tag = 0;
            uint8_t wrieType = std::log(sizeof(T)) / std::log(2);
            tag = wrieType;
            tag = tag << 12;
            tag += dataId & 0x0FFF;

            SerializeTag(tag);
        
            Serialize(value.value());
        }
    }
    
    template <typename T>
    void Serialize(uint16_t dataId, const ara::core::Optional<T>& value, typename std::enable_if<is_enumerable<T>::value>::type* = 0)
    {        
        if (value.has_value())
        {
            SerializeStructTag(dataId);

            value.value().Serialize(this);
        }
    }
    
    template <typename T>
    void Serialize(uint16_t dataId, const ara::core::Optional<std::vector<T>>& value)
    {
        if (value.has_value())
        {
            SerializeVectorTag(dataId);

            Serialize(value.value());
        }
    }
    
    template <typename T, std::size_t SIZE>
    void Serialize(uint16_t dataId, const ara::core::Optional<std::array<T,SIZE>>& value)
    {
        if (value.has_value())
        {
            SerializeArrayTag(dataId);

            uint32_t beginSize = m_container->size();
			
            Serialize(value.value());
            
            SerializeArraySize(beginSize);
        }
    }
    
    template <typename KEY, typename VALUE>
    void Serialize(uint16_t dataId, const ara::core::Optional<std::map<KEY,VALUE>>& value)
    {
        if (value.has_value())
        {
            SerializeMapTag(dataId);

            Serialize(value.value());
        }
    }
    
protected:
    std::shared_ptr<std::vector<uint8_t>> m_container;
//    std::shared_ptr<ApTransformationProps> m_transformationProps;
};

} // binding
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_BINDING_SERIALIZER_H_
