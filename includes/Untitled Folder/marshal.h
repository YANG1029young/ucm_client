/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_BINDING_MARSHAL_H_
#define ARA_COM_INTERNAL_BINDING_MARSHAL_H_

#include <type_traits>

#include <ara/com/internal/common.h>
#include <ara/com/internal/binding/deserializer.h>

namespace ara
{
namespace com
{
namespace internal
{
namespace binding
{

template <std::size_t I, typename Head, typename... Tail>
struct ArgumentTypeImpl
{
    using type = typename ArgumentTypeImpl<I - 1, Tail...>::type;
};

template <typename Head, typename... Tail>
struct ArgumentTypeImpl<0, Head, Tail...>
{
    using type = Head;
};

template <std::size_t I, typename... Args>
using ArgumentType = typename ArgumentTypeImpl<I, Args...>::type;

template <std::size_t I, typename... Args>
struct MessageIndexerImpl
{
    template <typename OutputIter>
    void operator()(std::shared_ptr<Deserializer> deserializer, std::size_t cur_pos, const std::uint8_t* data, std::size_t size, OutputIter out)
    {
        *out = cur_pos;

        typename std::decay<ArgumentType<sizeof...(Args) - I - 1, Args...>>::type value;
        std::size_t arg_size = deserializer->Deserialize(value, data + cur_pos, size - cur_pos);
        
        if (arg_size == 0)
        {
            invalidArgData = true;
            return;
        }
        
        MessageIndexerImpl<I - 1, Args...> next;
        next(deserializer, cur_pos + arg_size, data, size, ++out);
        
        invalidArgData = next.invalidArgData;
    }
    
    bool invalidArgData = false;
};

template <typename... Args>
struct MessageIndexerImpl<0, Args...>
{
    template <typename OutputIter>
    void operator()(std::shared_ptr<Deserializer> deserializer, std::size_t cur_pos, const std::uint8_t* data, std::size_t size, OutputIter out)
    {
        *out = cur_pos;
    }
    
    bool invalidArgData = false;
};

template <typename... Args>
class Unmarshaller
{
public:
    Unmarshaller(std::shared_ptr<Deserializer> deserializer, const uint8_t *data, uint32_t size)
        :m_deserializer(deserializer), m_data(data), m_size(size), m_positions()
    {        
        IndexMessage();
    }
    
    virtual ~Unmarshaller(){}
    
    template <std::size_t I>
    typename std::decay<ArgumentType<I, Args...>>::type unmarshal()
    {
        static_assert(I < sizeof...(Args), "Argument index out of bounds!");
        std::size_t pos = m_positions[I];
        
        typename std::decay<ArgumentType<I, Args...>>::type value;
        m_deserializer->Deserialize(value, m_data + pos, m_size - pos);
        
        return value;
    }
    
    bool hasInvalidArgData()
    {
        return m_invalidArgData;
    }
    
private:
    void IndexMessage()
    {
        MessageIndexerImpl<sizeof...(Args) - 1, Args...> indexer;
        indexer(m_deserializer, 0, m_data, m_size, &m_positions[0]);
        
        m_invalidArgData = indexer.invalidArgData;
    };
    
    std::shared_ptr<Deserializer> m_deserializer;
    const std::uint8_t* m_data;
    std::size_t m_size; 
    std::array<std::size_t, sizeof...(Args)> m_positions;
    bool m_invalidArgData = false;
};

} // binding
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_BINDING_MARSHAL_H_s
